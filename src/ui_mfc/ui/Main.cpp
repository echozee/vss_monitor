#include <afxwin.h>

class VssMonApp : public CWinApp {
public:
    BOOL InitInstance() override {
        CWinApp::InitInstance();
        // No UI yet; exit immediately
        return FALSE;
    }
};

VssMonApp theApp;
