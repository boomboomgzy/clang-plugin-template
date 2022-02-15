#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Frontend/FrontendPluginRegistry.h"

namespace astexp {

  // Sample AST plugin courtesy of nsumner.
  // (https://github.com/nsumner/clang-plugins-demo)

  class PrintFunctionsAction : public clang::PluginASTAction {
  public:
    PrintFunctionsAction()
      { }

    std::unique_ptr<clang::ASTConsumer>
    CreateASTConsumer(clang::CompilerInstance &ci, llvm::StringRef) override {
      ci.getDiagnostics().setClient(new clang::IgnoringDiagConsumer());
      return std::make_unique<clang::ASTConsumer>();
    }

    bool
    ParseArgs(const clang::CompilerInstance &ci,
              const std::vector<std::string>& args) override {
      return true;
    }

  protected:
    void EndSourceFileAction() override;

    clang::PluginASTAction::ActionType
    getActionType() override {
      return ReplaceAction;
    }
  };


  static clang::FrontendPluginRegistry::Add<PrintFunctionsAction>
    X("function-printer-demo", "Print the names of functions inside the file.");


  class FunctionNameVisitor :
    public clang::RecursiveASTVisitor<FunctionNameVisitor> {
  public:
    bool
    VisitFunctionDecl(clang::FunctionDecl *f) {
      llvm::outs() << "Function "
                   << (f->hasBody() ? "Def" : "Decl")
                   << " "
                   << f->getNameInfo().getName()
                   << "\n";
      return true;
    }
  };


  void
  PrintFunctionsAction::EndSourceFileAction() {
    auto &ci      = getCompilerInstance();
    auto &context = ci.getASTContext();

    auto &input = getCurrentInput();
    llvm::StringRef fileName = input.getFile();
    llvm::outs() << "Filename in Action: " << fileName << "\n";

    auto *unit = context.getTranslationUnitDecl();
    FunctionNameVisitor visitor;
    visitor.TraverseDecl(unit);

    clang::ASTFrontendAction::EndSourceFileAction();
  }

}
