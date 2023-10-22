#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Frontend/FrontendPluginRegistry.h"

namespace printfunc {

  class PrintFunctionsAction : public clang::PluginASTAction {
  public:
    PrintFunctionsAction()
      { }
    std::unique_ptr<clang::ASTConsumer>
    CreateASTConsumer(clang::CompilerInstance &ci, llvm::StringRef) override {
      ci.getDiagnostics().setClient(new clang::IgnoringDiagConsumer());
      return std::make_unique<clang::ASTConsumer>();
    }
//添加参数格式：-fplugin-arg-<plugin name>-<argument>
//示例：-fplugin-arg-call_super_plugin-help 
    bool
    ParseArgs(const clang::CompilerInstance &ci,
              const std::vector<std::string>& args) override {
      return true;
    }

  protected:
    //do something before source file parse
    virtual bool BeginSourceFileAction(clang::CompilerInstance& ci) override;
    //do something after source file parse
    virtual void EndSourceFileAction() override;
    //ActionType to be test
    clang::PluginASTAction::ActionType getActionType() override {
      return ReplaceAction;
    }
  };

  //注册插件
  static clang::FrontendPluginRegistry::Add<PrintFunctionsAction>
    X("function-printer-demo", "Print the names of functions inside the file.");


  class FunctionNameVisitor :public clang::RecursiveASTVisitor<FunctionNameVisitor> {

  public:
    FunctionNameVisitor(clang::ASTContext& context) : context(context) {}
  //在访问到函数节点时触发
    bool
    VisitFunctionDecl(clang::FunctionDecl *f) {
      //输出遍历到的FunctionDecl节点
      f->dump();

      //访问函数的位置
      clang::FullSourceLoc functionloc=context.getFullLoc(f->getBeginLoc());
      if(functionloc.isValid()){
        //格式 line_num:col_num
        functionloc.dump();
      }

      llvm::outs() << "Function "
                   << (f->hasBody() ? "Def" : "Decl")
                   << " "
                   << f->getNameInfo().getName()
                   << "\n";

      return true;
    }

    private:
      clang::ASTContext& context;
  };

  bool PrintFunctionsAction::BeginSourceFileAction(clang::CompilerInstance& ci){
    //llvm::outs()<<"Begin Action!"<<"\n";

    return clang::ASTFrontendAction::BeginSourceFileAction(ci);
  }

  void PrintFunctionsAction::EndSourceFileAction() {
    auto &ci      = getCompilerInstance();
    auto &context = ci.getASTContext();


    auto &input = getCurrentInput();
    llvm::StringRef fileName = input.getFile();
    llvm::outs() << "Filename in Action: " << fileName << "\n";

    auto *unit = context.getTranslationUnitDecl();
    FunctionNameVisitor visitor(context);
    visitor.TraverseDecl(unit);

    clang::ASTFrontendAction::EndSourceFileAction();
  } 

}
