
#include <wx/wx.h>
#include <wx/taskbar.h>

class MyTaskBarIcon : public wxTaskBarIcon
{
public:
    MyTaskBarIcon() {}

    wxMenu* CreatePopupMenu() override {
        wxMenu* menu = new wxMenu;
        menu->Append(wxID_EXIT, "Exit");
        Bind(wxEVT_MENU, &MyTaskBarIcon::OnExit, this, wxID_EXIT);
        return menu;
    }

private:
    void OnExit(wxCommandEvent&) {
        wxTheApp->Exit();
    }
};

class MyApp : public wxApp
{
private:
    MyTaskBarIcon* m_taskBarIcon;

public:
    bool OnInit() override {
        if (!wxApp::OnInit())
            return false;

        m_taskBarIcon = new MyTaskBarIcon();
        
        // Load and set the icon
        wxIcon icon;
        icon.LoadFile("sample.ico", wxBITMAP_TYPE_ICO);    
            
        if (!m_taskBarIcon->SetIcon(icon, "My System Tray App")) {
            wxMessageBox("Could not set icon.");
            return false;
        }

        return true;
    }

    int OnExit() override {
        delete m_taskBarIcon;
        return wxApp::OnExit();
    }
};

wxIMPLEMENT_APP(MyApp);
