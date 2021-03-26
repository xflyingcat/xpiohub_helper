/***************************************************************
 * Name:      loggerMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2019-02-12
 * Copyright:  ()
 * License:
 **************************************************************/

#include "loggerMain.h"
#include <wx/msgdlg.h>
#include "Serial.h"
#include "serial_enum.h"
#include "logger.h"
#include "wx/config.h"
#include "console_utils.h"

#define __CONFIG_NAME__  "XPIOHubConfigHelperExtIO"

#define clYellow     wxColour(255,255,0)
#define clAqua       wxColour(0,255,255)
#define clWhite      wxColour(255,255,255)
#define clLime       wxColour(0,255,0)
#define clRed        wxColour(255,0,0)
#define clBlue        wxColour(0,0,255)
#define clGray        wxColour(176,176,176)
#define clDarkGreen   wxColour(0,176,0)
#define clDarkYellow  wxColour(128,128,0)
#define clBlack       wxColour(0,0,0)

loggerDialog *logger_dialog;
int current_panel = 0;




char display_array[48*8+5];
char led_array[16*8*8+5];

int timer_enabled = 0;

wxTextCtrl *axes[16];



int rx_call_back(char *rxbuf, int rxlen);
int udp_call_back(char *rxbuf, int rxlen);

//(*InternalHeaders(loggerDialog)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat
{
    short_f, long_f
};

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(loggerDialog)
const long loggerDialog::ID_STATICTEXT6 = wxNewId();
const long loggerDialog::ID_TEXTCTRL2 = wxNewId();
const long loggerDialog::ID_STATICTEXT12 = wxNewId();
const long loggerDialog::ID_TEXTCTRL7 = wxNewId();
const long loggerDialog::ID_STATICLINE5 = wxNewId();
const long loggerDialog::ID_STATICTEXT15 = wxNewId();
const long loggerDialog::ID_TEXTCTRL25 = wxNewId();
const long loggerDialog::ID_STATICTEXT68 = wxNewId();
const long loggerDialog::ID_TEXTCTRL10 = wxNewId();
const long loggerDialog::ID_STATICLINE2 = wxNewId();
const long loggerDialog::ID_CHOICE2 = wxNewId();
const long loggerDialog::ID_STATICTEXT5 = wxNewId();
const long loggerDialog::ID_CHOICE1 = wxNewId();
const long loggerDialog::ID_STATICTEXT3 = wxNewId();
const long loggerDialog::ID_STATICTEXT4 = wxNewId();
const long loggerDialog::ID_TEXTCTRL1 = wxNewId();
const long loggerDialog::ID_STATICTEXT27 = wxNewId();
const long loggerDialog::ID_TEXTCTRL17 = wxNewId();
const long loggerDialog::ID_BUTTON5 = wxNewId();
const long loggerDialog::ID_STATICTEXT14 = wxNewId();
const long loggerDialog::ID_TEXTCTRL9 = wxNewId();
const long loggerDialog::ID_STATICTEXT13 = wxNewId();
const long loggerDialog::ID_TEXTCTRL8 = wxNewId();
const long loggerDialog::ID_STATICTEXT11 = wxNewId();
const long loggerDialog::ID_TEXTCTRL6 = wxNewId();
const long loggerDialog::ID_STATICTEXT8 = wxNewId();
const long loggerDialog::ID_TEXTCTRL3 = wxNewId();
const long loggerDialog::ID_STATICTEXT9 = wxNewId();
const long loggerDialog::ID_TEXTCTRL4 = wxNewId();
const long loggerDialog::ID_STATICTEXT10 = wxNewId();
const long loggerDialog::ID_TEXTCTRL5 = wxNewId();
const long loggerDialog::ID_PANEL1 = wxNewId();
const long loggerDialog::ID_STATICTEXT61 = wxNewId();
const long loggerDialog::ID_TEXTCTRL59 = wxNewId();
const long loggerDialog::ID_STATICTEXT64 = wxNewId();
const long loggerDialog::ID_TEXTCTRL60 = wxNewId();
const long loggerDialog::ID_STATICTEXT62 = wxNewId();
const long loggerDialog::ID_TEXTCTRL61 = wxNewId();
const long loggerDialog::ID_STATICTEXT63 = wxNewId();
const long loggerDialog::ID_TEXTCTRL62 = wxNewId();
const long loggerDialog::ID_STATICLINE3 = wxNewId();
const long loggerDialog::ID_CHOICE7 = wxNewId();
const long loggerDialog::ID_STATICTEXT31 = wxNewId();
const long loggerDialog::ID_STATICTEXT56 = wxNewId();
const long loggerDialog::ID_TEXTCTRL49 = wxNewId();
const long loggerDialog::ID_STATICTEXT34 = wxNewId();
const long loggerDialog::ID_TEXTCTRL46 = wxNewId();
const long loggerDialog::ID_STATICLINE4 = wxNewId();
const long loggerDialog::ID_BUTTON18 = wxNewId();
const long loggerDialog::ID_TEXTCTRL50 = wxNewId();
const long loggerDialog::ID_STATICTEXT57 = wxNewId();
const long loggerDialog::ID_TEXTCTRL51 = wxNewId();
const long loggerDialog::ID_BUTTON19 = wxNewId();
const long loggerDialog::ID_TEXTCTRL56 = wxNewId();
const long loggerDialog::ID_STATICTEXT58 = wxNewId();
const long loggerDialog::ID_TEXTCTRL57 = wxNewId();
const long loggerDialog::ID_BUTTON20 = wxNewId();
const long loggerDialog::ID_TEXTCTRL58 = wxNewId();
const long loggerDialog::ID_STATICTEXT60 = wxNewId();
const long loggerDialog::ID_CHECKBOX4 = wxNewId();
const long loggerDialog::ID_STATICLINE11 = wxNewId();
const long loggerDialog::ID_BUTTON21 = wxNewId();
const long loggerDialog::ID_PANEL6 = wxNewId();
const long loggerDialog::ID_CHOICE4 = wxNewId();
const long loggerDialog::ID_STATICTEXT18 = wxNewId();
const long loggerDialog::ID_CHOICE3 = wxNewId();
const long loggerDialog::ID_STATICTEXT16 = wxNewId();
const long loggerDialog::ID_STATICTEXT17 = wxNewId();
const long loggerDialog::ID_TEXTCTRL11 = wxNewId();
const long loggerDialog::ID_STATICTEXT20 = wxNewId();
const long loggerDialog::ID_TEXTCTRL13 = wxNewId();
const long loggerDialog::ID_STATICTEXT19 = wxNewId();
const long loggerDialog::ID_TEXTCTRL12 = wxNewId();
const long loggerDialog::ID_BUTTON6 = wxNewId();
const long loggerDialog::ID_STATICTEXT21 = wxNewId();
const long loggerDialog::ID_TEXTCTRL14 = wxNewId();
const long loggerDialog::ID_STATICTEXT22 = wxNewId();
const long loggerDialog::ID_TEXTCTRL15 = wxNewId();
const long loggerDialog::ID_STATICTEXT23 = wxNewId();
const long loggerDialog::ID_TEXTCTRL16 = wxNewId();
const long loggerDialog::ID_STATICTEXT29 = wxNewId();
const long loggerDialog::ID_TEXTCTRL21 = wxNewId();
const long loggerDialog::ID_STATICTEXT25 = wxNewId();
const long loggerDialog::ID_TEXTCTRL18 = wxNewId();
const long loggerDialog::ID_STATICTEXT26 = wxNewId();
const long loggerDialog::ID_TEXTCTRL19 = wxNewId();
const long loggerDialog::ID_STATICTEXT28 = wxNewId();
const long loggerDialog::ID_TEXTCTRL20 = wxNewId();
const long loggerDialog::ID_CHECKBOX1 = wxNewId();
const long loggerDialog::ID_STATICTEXT7 = wxNewId();
const long loggerDialog::ID_TEXTCTRL23 = wxNewId();
const long loggerDialog::ID_BUTTON15 = wxNewId();
const long loggerDialog::ID_TEXTCTRL24 = wxNewId();
const long loggerDialog::ID_BUTTON16 = wxNewId();
const long loggerDialog::ID_TEXTCTRL45 = wxNewId();
const long loggerDialog::ID_BUTTON17 = wxNewId();
const long loggerDialog::ID_STATICLINE12 = wxNewId();
const long loggerDialog::ID_STATICTEXT69 = wxNewId();
const long loggerDialog::ID_PANEL2 = wxNewId();
const long loggerDialog::ID_STATICTEXT35 = wxNewId();
const long loggerDialog::ID_TEXTCTRL30 = wxNewId();
const long loggerDialog::ID_STATICTEXT33 = wxNewId();
const long loggerDialog::ID_TEXTCTRL26 = wxNewId();
const long loggerDialog::ID_STATICTEXT36 = wxNewId();
const long loggerDialog::ID_TEXTCTRL27 = wxNewId();
const long loggerDialog::ID_STATICTEXT37 = wxNewId();
const long loggerDialog::ID_TEXTCTRL28 = wxNewId();
const long loggerDialog::ID_STATICTEXT38 = wxNewId();
const long loggerDialog::ID_TEXTCTRL29 = wxNewId();
const long loggerDialog::ID_STATICTEXT39 = wxNewId();
const long loggerDialog::ID_TEXTCTRL31 = wxNewId();
const long loggerDialog::ID_STATICTEXT40 = wxNewId();
const long loggerDialog::ID_TEXTCTRL32 = wxNewId();
const long loggerDialog::ID_STATICTEXT41 = wxNewId();
const long loggerDialog::ID_TEXTCTRL33 = wxNewId();
const long loggerDialog::ID_STATICTEXT42 = wxNewId();
const long loggerDialog::ID_TEXTCTRL34 = wxNewId();
const long loggerDialog::ID_STATICTEXT43 = wxNewId();
const long loggerDialog::ID_TEXTCTRL35 = wxNewId();
const long loggerDialog::ID_STATICTEXT44 = wxNewId();
const long loggerDialog::ID_TEXTCTRL36 = wxNewId();
const long loggerDialog::ID_STATICTEXT45 = wxNewId();
const long loggerDialog::ID_TEXTCTRL37 = wxNewId();
const long loggerDialog::ID_STATICTEXT46 = wxNewId();
const long loggerDialog::ID_TEXTCTRL38 = wxNewId();
const long loggerDialog::ID_STATICTEXT47 = wxNewId();
const long loggerDialog::ID_TEXTCTRL39 = wxNewId();
const long loggerDialog::ID_STATICTEXT48 = wxNewId();
const long loggerDialog::ID_TEXTCTRL40 = wxNewId();
const long loggerDialog::ID_STATICTEXT49 = wxNewId();
const long loggerDialog::ID_TEXTCTRL41 = wxNewId();
const long loggerDialog::ID_CHOICE6 = wxNewId();
const long loggerDialog::ID_STATICTEXT52 = wxNewId();
const long loggerDialog::ID_CHOICE5 = wxNewId();
const long loggerDialog::ID_STATICTEXT50 = wxNewId();
const long loggerDialog::ID_STATICTEXT53 = wxNewId();
const long loggerDialog::ID_TEXTCTRL42 = wxNewId();
const long loggerDialog::ID_STATICTEXT54 = wxNewId();
const long loggerDialog::ID_TEXTCTRL43 = wxNewId();
const long loggerDialog::ID_STATICTEXT59 = wxNewId();
const long loggerDialog::ID_TEXTCTRL48 = wxNewId();
const long loggerDialog::ID_BUTTON12 = wxNewId();
const long loggerDialog::ID_TEXTCTRL44 = wxNewId();
const long loggerDialog::ID_STATICTEXT65 = wxNewId();
const long loggerDialog::ID_TEXTCTRL54 = wxNewId();
const long loggerDialog::ID_BUTTON13 = wxNewId();
const long loggerDialog::ID_TEXTCTRL52 = wxNewId();
const long loggerDialog::ID_STATICTEXT66 = wxNewId();
const long loggerDialog::ID_TEXTCTRL55 = wxNewId();
const long loggerDialog::ID_BUTTON14 = wxNewId();
const long loggerDialog::ID_TEXTCTRL53 = wxNewId();
const long loggerDialog::ID_STATICTEXT67 = wxNewId();
const long loggerDialog::ID_CHECKBOX3 = wxNewId();
const long loggerDialog::ID_BUTTON10 = wxNewId();
const long loggerDialog::ID_PANEL3 = wxNewId();
const long loggerDialog::ID_GRID1 = wxNewId();
const long loggerDialog::ID_BUTTON7 = wxNewId();
const long loggerDialog::ID_PANEL4 = wxNewId();
const long loggerDialog::ID_GRID2 = wxNewId();
const long loggerDialog::ID_BUTTON11 = wxNewId();
const long loggerDialog::ID_PANEL5 = wxNewId();
const long loggerDialog::ID_NOTEBOOK1 = wxNewId();
const long loggerDialog::ID_COMBOBOX3 = wxNewId();
const long loggerDialog::ID_STATICTEXT70 = wxNewId();
const long loggerDialog::ID_BUTTON24 = wxNewId();
const long loggerDialog::ID_COMBOBOX4 = wxNewId();
const long loggerDialog::ID_STATICTEXT71 = wxNewId();
const long loggerDialog::ID_STATICLINE1 = wxNewId();
const long loggerDialog::ID_STATICTEXT1 = wxNewId();
const long loggerDialog::ID_TEXTCTRL22 = wxNewId();
const long loggerDialog::ID_STATICTEXT2 = wxNewId();
const long loggerDialog::ID_STATICLINE7 = wxNewId();
const long loggerDialog::ID_STATICTEXT24 = wxNewId();
const long loggerDialog::ID_BUTTON4 = wxNewId();
const long loggerDialog::ID_COMBOBOX1 = wxNewId();
const long loggerDialog::ID_STATICTEXT51 = wxNewId();
const long loggerDialog::ID_COMBOBOX2 = wxNewId();
const long loggerDialog::ID_BUTTON1 = wxNewId();
const long loggerDialog::ID_BUTTON8 = wxNewId();
const long loggerDialog::ID_BUTTON2 = wxNewId();
const long loggerDialog::ID_STATICLINE8 = wxNewId();
const long loggerDialog::ID_STATICTEXT55 = wxNewId();
const long loggerDialog::ID_STATICTEXT32 = wxNewId();
const long loggerDialog::ID_TEXTCTRL47 = wxNewId();
const long loggerDialog::ID_BUTTON22 = wxNewId();
const long loggerDialog::ID_BUTTON23 = wxNewId();
const long loggerDialog::ID_STATICLINE9 = wxNewId();
const long loggerDialog::ID_STATICLINE10 = wxNewId();
const long loggerDialog::ID_STATICTEXT30 = wxNewId();
const long loggerDialog::ID_BUTTON9 = wxNewId();
const long loggerDialog::ID_CHECKBOX2 = wxNewId();
const long loggerDialog::ID_STATICLINE6 = wxNewId();
const long loggerDialog::ID_BUTTON3 = wxNewId();
const long loggerDialog::ID_TIMER1 = wxNewId();
const long loggerDialog::ID_TIMER2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(loggerDialog,wxDialog)
    //(*EventTable(loggerDialog)
    //*)
END_EVENT_TABLE()

loggerDialog::loggerDialog(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(loggerDialog)
    wxBoxSizer* BoxSizer10;
    wxBoxSizer* BoxSizer11;
    wxBoxSizer* BoxSizer12;
    wxBoxSizer* BoxSizer13;
    wxBoxSizer* BoxSizer14;
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer3;
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer5;
    wxBoxSizer* BoxSizer6;
    wxBoxSizer* BoxSizer7;
    wxBoxSizer* BoxSizer8;
    wxBoxSizer* BoxSizer9;
    wxFlexGridSizer* FlexGridSizer10;
    wxFlexGridSizer* FlexGridSizer11;
    wxFlexGridSizer* FlexGridSizer12;
    wxFlexGridSizer* FlexGridSizer13;
    wxFlexGridSizer* FlexGridSizer14;
    wxFlexGridSizer* FlexGridSizer15;
    wxFlexGridSizer* FlexGridSizer16;
    wxFlexGridSizer* FlexGridSizer17;
    wxFlexGridSizer* FlexGridSizer18;
    wxFlexGridSizer* FlexGridSizer19;
    wxFlexGridSizer* FlexGridSizer1;
    wxFlexGridSizer* FlexGridSizer20;
    wxFlexGridSizer* FlexGridSizer21;
    wxFlexGridSizer* FlexGridSizer22;
    wxFlexGridSizer* FlexGridSizer23;
    wxFlexGridSizer* FlexGridSizer24;
    wxFlexGridSizer* FlexGridSizer25;
    wxFlexGridSizer* FlexGridSizer26;
    wxFlexGridSizer* FlexGridSizer27;
    wxFlexGridSizer* FlexGridSizer28;
    wxFlexGridSizer* FlexGridSizer29;
    wxFlexGridSizer* FlexGridSizer2;
    wxFlexGridSizer* FlexGridSizer30;
    wxFlexGridSizer* FlexGridSizer31;
    wxFlexGridSizer* FlexGridSizer32;
    wxFlexGridSizer* FlexGridSizer33;
    wxFlexGridSizer* FlexGridSizer34;
    wxFlexGridSizer* FlexGridSizer35;
    wxFlexGridSizer* FlexGridSizer36;
    wxFlexGridSizer* FlexGridSizer37;
    wxFlexGridSizer* FlexGridSizer38;
    wxFlexGridSizer* FlexGridSizer39;
    wxFlexGridSizer* FlexGridSizer3;
    wxFlexGridSizer* FlexGridSizer40;
    wxFlexGridSizer* FlexGridSizer41;
    wxFlexGridSizer* FlexGridSizer42;
    wxFlexGridSizer* FlexGridSizer43;
    wxFlexGridSizer* FlexGridSizer44;
    wxFlexGridSizer* FlexGridSizer45;
    wxFlexGridSizer* FlexGridSizer46;
    wxFlexGridSizer* FlexGridSizer47;
    wxFlexGridSizer* FlexGridSizer48;
    wxFlexGridSizer* FlexGridSizer49;
    wxFlexGridSizer* FlexGridSizer4;
    wxFlexGridSizer* FlexGridSizer50;
    wxFlexGridSizer* FlexGridSizer51;
    wxFlexGridSizer* FlexGridSizer52;
    wxFlexGridSizer* FlexGridSizer53;
    wxFlexGridSizer* FlexGridSizer54;
    wxFlexGridSizer* FlexGridSizer55;
    wxFlexGridSizer* FlexGridSizer56;
    wxFlexGridSizer* FlexGridSizer57;
    wxFlexGridSizer* FlexGridSizer58;
    wxFlexGridSizer* FlexGridSizer59;
    wxFlexGridSizer* FlexGridSizer5;
    wxFlexGridSizer* FlexGridSizer6;
    wxFlexGridSizer* FlexGridSizer7;
    wxFlexGridSizer* FlexGridSizer8;
    wxFlexGridSizer* FlexGridSizer9;
    wxGridSizer* GridSizer1;
    wxGridSizer* GridSizer2;
    wxGridSizer* GridSizer3;
    wxGridSizer* GridSizer4;
    wxGridSizer* GridSizer5;
    wxGridSizer* GridSizer6;
    wxGridSizer* GridSizer7;

    Create(parent, wxID_ANY, _("wxWidgets app"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
    FlexGridSizer1 = new wxFlexGridSizer(3, 1, 0, 0);
    FlexGridSizer2 = new wxFlexGridSizer(3, 6, 0, 0);
    FlexGridSizer25 = new wxFlexGridSizer(5, 1, 0, 0);
    StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Remarks"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    FlexGridSizer25->Add(StaticText6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    TextCtrl2 = new wxTextCtrl(this, ID_TEXTCTRL2, _("Some comment (remove all to omit comments)"), wxDefaultPosition, wxSize(399,64), wxTE_AUTO_SCROLL|wxTE_MULTILINE, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    FlexGridSizer25->Add(TextCtrl2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText12 = new wxStaticText(this, ID_STATICTEXT12, _("Result section for ini file"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    FlexGridSizer25->Add(StaticText12, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    TextCtrl7 = new wxTextCtrl(this, ID_TEXTCTRL7, wxEmptyString, wxDefaultPosition, wxSize(411,407), wxTE_AUTO_SCROLL|wxTE_MULTILINE, wxDefaultValidator, _T("ID_TEXTCTRL7"));
    FlexGridSizer25->Add(TextCtrl7, 1, wxALL|wxEXPAND, 5);
    StaticLine5 = new wxStaticLine(this, ID_STATICLINE5, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE5"));
    FlexGridSizer25->Add(StaticLine5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2->Add(FlexGridSizer25, 1, wxALL|wxEXPAND, 0);
    FlexGridSizer3 = new wxFlexGridSizer(22, 1, 0, 0);
    Notebook1 = new wxNotebook(this, ID_NOTEBOOK1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_NOTEBOOK1"));
    Panel1 = new wxPanel(Notebook1, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    FlexGridSizer27 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer51 = new wxFlexGridSizer(0, 10, 0, 0);
    StaticText15 = new wxStaticText(Panel1, ID_STATICTEXT15, _("Last control event:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
    FlexGridSizer51->Add(StaticText15, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl25 = new wxTextCtrl(Panel1, ID_TEXTCTRL25, wxEmptyString, wxDefaultPosition, wxSize(126,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL25"));
    FlexGridSizer51->Add(TextCtrl25, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer51->Add(8,34,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    StaticText68 = new wxStaticText(Panel1, ID_STATICTEXT68, _("EvID(decimal)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT68"));
    FlexGridSizer51->Add(StaticText68, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    TextCtrl10 = new wxTextCtrl(Panel1, ID_TEXTCTRL10, wxEmptyString, wxDefaultPosition, wxSize(50,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL10"));
    FlexGridSizer51->Add(TextCtrl10, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer51->Add(6,34,1, wxALL|wxEXPAND, 0);
    FlexGridSizer27->Add(FlexGridSizer51, 1, wxALL|wxEXPAND, 0);
    StaticLine2 = new wxStaticLine(Panel1, ID_STATICLINE2, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE2"));
    FlexGridSizer27->Add(StaticLine2, 1, wxALL|wxEXPAND, 0);
    FlexGridSizer7 = new wxFlexGridSizer(10, 1, 0, 0);
    FlexGridSizer17 = new wxFlexGridSizer(0, 3, 0, 0);
    Choice2 = new wxChoice(Panel1, ID_CHOICE2, wxDefaultPosition, wxSize(117,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
    Choice2->Append(wxEmptyString);
    Choice2->SetSelection( Choice2->Append(_("Button")) );
    Choice2->Append(_("Cyclic button"));
    Choice2->Append(_("Toggle switch"));
    Choice2->Append(_("Rotary switch position"));
    Choice2->Append(_("Encoder"));
    FlexGridSizer17->Add(Choice2, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticText5 = new wxStaticText(Panel1, ID_STATICTEXT5, _("Control type"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    FlexGridSizer17->Add(StaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    FlexGridSizer7->Add(FlexGridSizer17, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer18 = new wxFlexGridSizer(0, 3, 0, 0);
    Choice1 = new wxChoice(Panel1, ID_CHOICE1, wxDefaultPosition, wxSize(117,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    Choice1->Append(wxEmptyString);
    Choice1->SetSelection( Choice1->Append(_("Command")) );
    Choice1->Append(_("Dataref int"));
    Choice1->Append(_("Dataref float"));
    Choice1->Append(_("Array int"));
    Choice1->Append(_("Array float"));
    FlexGridSizer18->Add(Choice1, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticText3 = new wxStaticText(Panel1, ID_STATICTEXT3, _("Datref type"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    FlexGridSizer18->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    FlexGridSizer7->Add(FlexGridSizer18, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    StaticText4 = new wxStaticText(Panel1, ID_STATICTEXT4, _("Dataref / Command / Command_0"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    FlexGridSizer7->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl1 = new wxTextCtrl(Panel1, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(355,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    FlexGridSizer7->Add(TextCtrl1, 1, wxTOP|wxBOTTOM|wxEXPAND, 0);
    StaticText27 = new wxStaticText(Panel1, ID_STATICTEXT27, _("Command_1"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT27"));
    FlexGridSizer7->Add(StaticText27, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    TextCtrl17 = new wxTextCtrl(Panel1, ID_TEXTCTRL17, wxEmptyString, wxDefaultPosition, wxSize(362,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL17"));
    FlexGridSizer7->Add(TextCtrl17, 1, wxTOP|wxBOTTOM|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 3);
    FlexGridSizer27->Add(FlexGridSizer7, 1, wxALL|wxEXPAND, 0);
    FlexGridSizer5 = new wxFlexGridSizer(6, 1, 0, 0);
    FlexGridSizer8 = new wxFlexGridSizer(1, 3, 0, 0);
    FlexGridSizer11 = new wxFlexGridSizer(4, 1, 0, 0);
    Button5 = new wxButton(Panel1, ID_BUTTON5, _("Add control section"), wxDefaultPosition, wxSize(111,37), 0, wxDefaultValidator, _T("ID_BUTTON5"));
    FlexGridSizer11->Add(Button5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer8->Add(FlexGridSizer11, 1, wxALL|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 0);
    FlexGridSizer12 = new wxFlexGridSizer(6, 1, 0, 0);
    BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    StaticText14 = new wxStaticText(Panel1, ID_STATICTEXT14, _("0:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT14"));
    BoxSizer6->Add(StaticText14, 1, wxALL|wxALIGN_CENTER_VERTICAL, 3);
    TextCtrl9 = new wxTextCtrl(Panel1, ID_TEXTCTRL9, wxEmptyString, wxDefaultPosition, wxSize(50,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL9"));
    BoxSizer6->Add(TextCtrl9, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer12->Add(BoxSizer6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    StaticText13 = new wxStaticText(Panel1, ID_STATICTEXT13, _("1:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT13"));
    BoxSizer5->Add(StaticText13, 1, wxALL|wxALIGN_CENTER_VERTICAL, 3);
    TextCtrl8 = new wxTextCtrl(Panel1, ID_TEXTCTRL8, wxEmptyString, wxDefaultPosition, wxSize(50,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL8"));
    BoxSizer5->Add(TextCtrl8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer12->Add(BoxSizer5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    StaticText11 = new wxStaticText(Panel1, ID_STATICTEXT11, _("Index:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT11"));
    BoxSizer4->Add(StaticText11, 1, wxALL|wxALIGN_CENTER_VERTICAL, 3);
    TextCtrl6 = new wxTextCtrl(Panel1, ID_TEXTCTRL6, wxEmptyString, wxDefaultPosition, wxSize(50,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL6"));
    BoxSizer4->Add(TextCtrl6, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer12->Add(BoxSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer8->Add(FlexGridSizer12, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 0);
    FlexGridSizer23 = new wxFlexGridSizer(3, 1, 0, 0);
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    StaticText8 = new wxStaticText(Panel1, ID_STATICTEXT8, _("Min:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT8"));
    BoxSizer1->Add(StaticText8, 1, wxALL|wxALIGN_CENTER_VERTICAL, 3);
    TextCtrl3 = new wxTextCtrl(Panel1, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxSize(50,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    BoxSizer1->Add(TextCtrl3, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer23->Add(BoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    StaticText9 = new wxStaticText(Panel1, ID_STATICTEXT9, _("Max:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT9"));
    BoxSizer2->Add(StaticText9, 1, wxALL|wxALIGN_CENTER_VERTICAL, 2);
    TextCtrl4 = new wxTextCtrl(Panel1, ID_TEXTCTRL4, wxEmptyString, wxDefaultPosition, wxSize(50,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    BoxSizer2->Add(TextCtrl4, 1, wxALL|wxALIGN_TOP, 5);
    FlexGridSizer23->Add(BoxSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    StaticText10 = new wxStaticText(Panel1, ID_STATICTEXT10, _("Increment:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT10"));
    BoxSizer3->Add(StaticText10, 1, wxALL|wxALIGN_CENTER_VERTICAL, 3);
    TextCtrl5 = new wxTextCtrl(Panel1, ID_TEXTCTRL5, wxEmptyString, wxDefaultPosition, wxSize(33,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
    BoxSizer3->Add(TextCtrl5, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer23->Add(BoxSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer8->Add(FlexGridSizer23, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 0);
    FlexGridSizer5->Add(FlexGridSizer8, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer27->Add(FlexGridSizer5, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(FlexGridSizer27);
    FlexGridSizer27->Fit(Panel1);
    FlexGridSizer27->SetSizeHints(Panel1);
    Panel6 = new wxPanel(Notebook1, ID_PANEL6, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL6"));
    FlexGridSizer4 = new wxFlexGridSizer(10, 1, 0, 0);
    FlexGridSizer56 = new wxFlexGridSizer(0, 12, 0, 0);
    StaticText61 = new wxStaticText(Panel6, ID_STATICTEXT61, _("Last control event:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT61"));
    FlexGridSizer56->Add(StaticText61, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl59 = new wxTextCtrl(Panel6, ID_TEXTCTRL59, wxEmptyString, wxDefaultPosition, wxSize(126,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL59"));
    FlexGridSizer56->Add(TextCtrl59, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer56->Add(8,34,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    StaticText64 = new wxStaticText(Panel6, ID_STATICTEXT64, _("EvId(decimal)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT64"));
    FlexGridSizer56->Add(StaticText64, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    TextCtrl60 = new wxTextCtrl(Panel6, ID_TEXTCTRL60, wxEmptyString, wxDefaultPosition, wxSize(35,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL60"));
    FlexGridSizer56->Add(TextCtrl60, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer56->Add(6,34,1, wxALL|wxEXPAND, 0);
    FlexGridSizer4->Add(FlexGridSizer56, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer57 = new wxFlexGridSizer(0, 12, 0, 0);
    StaticText62 = new wxStaticText(Panel6, ID_STATICTEXT62, _("Event filter"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT62"));
    FlexGridSizer57->Add(StaticText62, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl61 = new wxTextCtrl(Panel6, ID_TEXTCTRL61, wxEmptyString, wxDefaultPosition, wxSize(63,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL61"));
    FlexGridSizer57->Add(TextCtrl61, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer57->Add(77,34,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    StaticText63 = new wxStaticText(Panel6, ID_STATICTEXT63, _("Current value"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT63"));
    FlexGridSizer57->Add(StaticText63, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl62 = new wxTextCtrl(Panel6, ID_TEXTCTRL62, wxEmptyString, wxDefaultPosition, wxSize(65,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL62"));
    FlexGridSizer57->Add(TextCtrl62, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(FlexGridSizer57, 1, wxALL|wxEXPAND, 0);
    StaticLine3 = new wxStaticLine(Panel6, ID_STATICLINE3, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE3"));
    FlexGridSizer4->Add(StaticLine3, 1, wxALL|wxEXPAND, 0);
    FlexGridSizer48 = new wxFlexGridSizer(8, 1, 0, 0);
    FlexGridSizer54 = new wxFlexGridSizer(1, 5, 0, 0);
    Choice7 = new wxChoice(Panel6, ID_CHOICE7, wxDefaultPosition, wxSize(103,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE7"));
    Choice7->Append(wxEmptyString);
    Choice7->SetSelection( Choice7->Append(_("Dataref int")) );
    Choice7->Append(_("Dataref float"));
    Choice7->Append(_("Array int"));
    Choice7->Append(_("Array float"));
    FlexGridSizer54->Add(Choice7, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText31 = new wxStaticText(Panel6, ID_STATICTEXT31, _("Dataref type"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT31"));
    FlexGridSizer54->Add(StaticText31, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
    FlexGridSizer54->Add(57,7,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText56 = new wxStaticText(Panel6, ID_STATICTEXT56, _("Index:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT56"));
    FlexGridSizer54->Add(StaticText56, 1, wxALL|wxALIGN_CENTER_VERTICAL, 1);
    TextCtrl49 = new wxTextCtrl(Panel6, ID_TEXTCTRL49, wxEmptyString, wxDefaultPosition, wxSize(27,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL49"));
    TextCtrl49->Disable();
    FlexGridSizer54->Add(TextCtrl49, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer48->Add(FlexGridSizer54, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    StaticText34 = new wxStaticText(Panel6, ID_STATICTEXT34, _("Dataref"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT34"));
    FlexGridSizer48->Add(StaticText34, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    TextCtrl46 = new wxTextCtrl(Panel6, ID_TEXTCTRL46, wxEmptyString, wxDefaultPosition, wxSize(359,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL46"));
    FlexGridSizer48->Add(TextCtrl46, 1, wxALL|wxEXPAND, 5);
    FlexGridSizer4->Add(FlexGridSizer48, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticLine4 = new wxStaticLine(Panel6, ID_STATICLINE4, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE4"));
    FlexGridSizer4->Add(StaticLine4, 1, wxALL|wxEXPAND, 0);
    GridSizer7 = new wxGridSizer(3, 4, 0, 0);
    Button18 = new wxButton(Panel6, ID_BUTTON18, _("DeviceMax >"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON18"));
    GridSizer7->Add(Button18, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    TextCtrl50 = new wxTextCtrl(Panel6, ID_TEXTCTRL50, wxEmptyString, wxDefaultPosition, wxSize(50,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL50"));
    GridSizer7->Add(TextCtrl50, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 3);
    StaticText57 = new wxStaticText(Panel6, ID_STATICTEXT57, _("SimMax:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT57"));
    GridSizer7->Add(StaticText57, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 1);
    TextCtrl51 = new wxTextCtrl(Panel6, ID_TEXTCTRL51, wxEmptyString, wxDefaultPosition, wxSize(50,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL51"));
    GridSizer7->Add(TextCtrl51, 1, wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    Button19 = new wxButton(Panel6, ID_BUTTON19, _("DevCenter >"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON19"));
    Button19->Disable();
    GridSizer7->Add(Button19, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    TextCtrl56 = new wxTextCtrl(Panel6, ID_TEXTCTRL56, wxEmptyString, wxDefaultPosition, wxSize(50,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL56"));
    TextCtrl56->Disable();
    GridSizer7->Add(TextCtrl56, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 3);
    StaticText58 = new wxStaticText(Panel6, ID_STATICTEXT58, _("SimMin:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT58"));
    GridSizer7->Add(StaticText58, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 1);
    TextCtrl57 = new wxTextCtrl(Panel6, ID_TEXTCTRL57, wxEmptyString, wxDefaultPosition, wxSize(50,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL57"));
    GridSizer7->Add(TextCtrl57, 1, wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    Button20 = new wxButton(Panel6, ID_BUTTON20, _("DeviceMin >"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON20"));
    GridSizer7->Add(Button20, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    TextCtrl58 = new wxTextCtrl(Panel6, ID_TEXTCTRL58, wxEmptyString, wxDefaultPosition, wxSize(50,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL58"));
    GridSizer7->Add(TextCtrl58, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 3);
    StaticText60 = new wxStaticText(Panel6, ID_STATICTEXT60, _("Has center:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT60"));
    GridSizer7->Add(StaticText60, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 1);
    CheckBox4 = new wxCheckBox(Panel6, ID_CHECKBOX4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
    CheckBox4->SetValue(false);
    GridSizer7->Add(CheckBox4, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(GridSizer7, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticLine11 = new wxStaticLine(Panel6, ID_STATICLINE11, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE11"));
    FlexGridSizer4->Add(StaticLine11, 1, wxALL|wxEXPAND, 0);
    Button21 = new wxButton(Panel6, ID_BUTTON21, _("Add Dataref  put section"), wxDefaultPosition, wxSize(148,32), 0, wxDefaultValidator, _T("ID_BUTTON21"));
    FlexGridSizer4->Add(Button21, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 3);
    Panel6->SetSizer(FlexGridSizer4);
    FlexGridSizer4->Fit(Panel6);
    FlexGridSizer4->SetSizeHints(Panel6);
    Panel2 = new wxPanel(Notebook1, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    FlexGridSizer9 = new wxFlexGridSizer(8, 1, 0, 0);
    FlexGridSizer13 = new wxFlexGridSizer(1, 3, 0, 0);
    FlexGridSizer16 = new wxFlexGridSizer(8, 1, 0, 0);
    FlexGridSizer10 = new wxFlexGridSizer(1, 2, 0, 0);
    Choice4 = new wxChoice(Panel2, ID_CHOICE4, wxDefaultPosition, wxSize(250,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE4"));
    Choice4->Append(wxEmptyString);
    Choice4->SetSelection( Choice4->Append(_("Numeric ( LCD, 7-seg ind. Servo/Stepper motors )")) );
    Choice4->Append(_("Discrete ( LEDs, Lamps, Power keys )"));
    FlexGridSizer10->Add(Choice4, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText18 = new wxStaticText(Panel2, ID_STATICTEXT18, _("Indication type"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
    FlexGridSizer10->Add(StaticText18, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer16->Add(FlexGridSizer10, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer14 = new wxFlexGridSizer(1, 2, 0, 0);
    Choice3 = new wxChoice(Panel2, ID_CHOICE3, wxDefaultPosition, wxSize(103,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE3"));
    Choice3->Append(wxEmptyString);
    Choice3->SetSelection( Choice3->Append(_("Dataref int")) );
    Choice3->Append(_("Dataref float"));
    Choice3->Append(_("Array int"));
    Choice3->Append(_("Array float"));
    FlexGridSizer14->Add(Choice3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText16 = new wxStaticText(Panel2, ID_STATICTEXT16, _("Dataref type"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
    FlexGridSizer14->Add(StaticText16, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 4);
    FlexGridSizer16->Add(FlexGridSizer14, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    StaticText17 = new wxStaticText(Panel2, ID_STATICTEXT17, _("Dataref"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
    FlexGridSizer16->Add(StaticText17, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    TextCtrl11 = new wxTextCtrl(Panel2, ID_TEXTCTRL11, wxEmptyString, wxDefaultPosition, wxSize(211,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL11"));
    FlexGridSizer16->Add(TextCtrl11, 1, wxALL|wxEXPAND, 0);
    FlexGridSizer13->Add(FlexGridSizer16, 1, wxALL|wxEXPAND, 3);
    FlexGridSizer9->Add(FlexGridSizer13, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer24 = new wxFlexGridSizer(0, 3, 0, 0);
    StaticText20 = new wxStaticText(Panel2, ID_STATICTEXT20, _("[section name]"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT20"));
    FlexGridSizer24->Add(StaticText20, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl13 = new wxTextCtrl(Panel2, ID_TEXTCTRL13, wxEmptyString, wxDefaultPosition, wxSize(210,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL13"));
    FlexGridSizer24->Add(TextCtrl13, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer9->Add(FlexGridSizer24, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer19 = new wxFlexGridSizer(1, 4, 0, 0);
    FlexGridSizer20 = new wxFlexGridSizer(4, 1, 0, 0);
    StaticText19 = new wxStaticText(Panel2, ID_STATICTEXT19, _("Data for indication test"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
    FlexGridSizer20->Add(StaticText19, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    TextCtrl12 = new wxTextCtrl(Panel2, ID_TEXTCTRL12, _("0"), wxDefaultPosition, wxSize(86,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL12"));
    FlexGridSizer20->Add(TextCtrl12, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer20->Add(20,19,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button6 = new wxButton(Panel2, ID_BUTTON6, _("Add indication section"), wxDefaultPosition, wxSize(123,38), 0, wxDefaultValidator, _T("ID_BUTTON6"));
    FlexGridSizer20->Add(Button6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer19->Add(FlexGridSizer20, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 0);
    FlexGridSizer21 = new wxFlexGridSizer(5, 1, 0, 0);
    BoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    StaticText21 = new wxStaticText(Panel2, ID_STATICTEXT21, _("*Device:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT21"));
    BoxSizer8->Add(StaticText21, 1, wxALL|wxALIGN_CENTER_VERTICAL, 1);
    TextCtrl14 = new wxTextCtrl(Panel2, ID_TEXTCTRL14, wxEmptyString, wxDefaultPosition, wxSize(50,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL14"));
    BoxSizer8->Add(TextCtrl14, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer21->Add(BoxSizer8, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
    StaticText22 = new wxStaticText(Panel2, ID_STATICTEXT22, _("**Position:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT22"));
    BoxSizer9->Add(StaticText22, 1, wxALL|wxALIGN_CENTER_VERTICAL, 1);
    TextCtrl15 = new wxTextCtrl(Panel2, ID_TEXTCTRL15, wxEmptyString, wxDefaultPosition, wxSize(50,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL15"));
    BoxSizer9->Add(TextCtrl15, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer21->Add(BoxSizer9, 1, wxALL|wxEXPAND, 0);
    BoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
    StaticText23 = new wxStaticText(Panel2, ID_STATICTEXT23, _("Length:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT23"));
    BoxSizer10->Add(StaticText23, 1, wxALL|wxALIGN_CENTER_VERTICAL, 1);
    TextCtrl16 = new wxTextCtrl(Panel2, ID_TEXTCTRL16, wxEmptyString, wxDefaultPosition, wxSize(50,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL16"));
    BoxSizer10->Add(TextCtrl16, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer21->Add(BoxSizer10, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
    StaticText29 = new wxStaticText(Panel2, ID_STATICTEXT29, _("Index"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT29"));
    BoxSizer7->Add(StaticText29, 1, wxALL|wxALIGN_CENTER_VERTICAL, 1);
    TextCtrl21 = new wxTextCtrl(Panel2, ID_TEXTCTRL21, wxEmptyString, wxDefaultPosition, wxSize(50,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL21"));
    BoxSizer7->Add(TextCtrl21, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer21->Add(BoxSizer7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer19->Add(FlexGridSizer21, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 0);
    FlexGridSizer22 = new wxFlexGridSizer(5, 1, 0, 0);
    BoxSizer12 = new wxBoxSizer(wxHORIZONTAL);
    StaticText25 = new wxStaticText(Panel2, ID_STATICTEXT25, _("Factor:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT25"));
    BoxSizer12->Add(StaticText25, 1, wxALL|wxALIGN_CENTER_VERTICAL, 1);
    TextCtrl18 = new wxTextCtrl(Panel2, ID_TEXTCTRL18, wxEmptyString, wxDefaultPosition, wxSize(50,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL18"));
    BoxSizer12->Add(TextCtrl18, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer22->Add(BoxSizer12, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer13 = new wxBoxSizer(wxHORIZONTAL);
    StaticText26 = new wxStaticText(Panel2, ID_STATICTEXT26, _("Offset:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT26"));
    BoxSizer13->Add(StaticText26, 1, wxALL|wxALIGN_CENTER_VERTICAL, 1);
    TextCtrl19 = new wxTextCtrl(Panel2, ID_TEXTCTRL19, wxEmptyString, wxDefaultPosition, wxSize(50,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL19"));
    BoxSizer13->Add(TextCtrl19, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer22->Add(BoxSizer13, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer14 = new wxBoxSizer(wxHORIZONTAL);
    StaticText28 = new wxStaticText(Panel2, ID_STATICTEXT28, _("Mask:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT28"));
    BoxSizer14->Add(StaticText28, 1, wxALL|wxALIGN_CENTER_VERTICAL, 1);
    TextCtrl20 = new wxTextCtrl(Panel2, ID_TEXTCTRL20, wxEmptyString, wxDefaultPosition, wxSize(50,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL20"));
    BoxSizer14->Add(TextCtrl20, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer22->Add(BoxSizer14, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer11 = new wxBoxSizer(wxHORIZONTAL);
    CheckBox1 = new wxCheckBox(Panel2, ID_CHECKBOX1, _("Show leading zeroes"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    CheckBox1->SetValue(false);
    BoxSizer11->Add(CheckBox1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer22->Add(BoxSizer11, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 0);
    FlexGridSizer19->Add(FlexGridSizer22, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 0);
    FlexGridSizer9->Add(FlexGridSizer19, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    StaticText7 = new wxStaticText(Panel2, ID_STATICTEXT7, _("Prepared data"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    FlexGridSizer9->Add(StaticText7, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer6 = new wxGridSizer(3, 2, 0, 0);
    TextCtrl23 = new wxTextCtrl(Panel2, ID_TEXTCTRL23, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL23"));
    GridSizer6->Add(TextCtrl23, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 3);
    Button15 = new wxButton(Panel2, ID_BUTTON15, _("Value 1 >"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON15"));
    GridSizer6->Add(Button15, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    TextCtrl24 = new wxTextCtrl(Panel2, ID_TEXTCTRL24, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL24"));
    GridSizer6->Add(TextCtrl24, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 3);
    Button16 = new wxButton(Panel2, ID_BUTTON16, _("Value 2 >"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON16"));
    GridSizer6->Add(Button16, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    TextCtrl45 = new wxTextCtrl(Panel2, ID_TEXTCTRL45, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL45"));
    GridSizer6->Add(TextCtrl45, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 3);
    Button17 = new wxButton(Panel2, ID_BUTTON17, _("Value 3 >"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON17"));
    GridSizer6->Add(Button17, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    FlexGridSizer9->Add(GridSizer6, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticLine12 = new wxStaticLine(Panel2, ID_STATICLINE12, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE12"));
    FlexGridSizer9->Add(StaticLine12, 1, wxALL|wxEXPAND, 0);
    StaticText69 = new wxStaticText(Panel2, ID_STATICTEXT69, _("*   means 8-symbols unit (one of 8)\n** offset within the device for alphanumeric device.\n     Absolute offset for discrete indicators"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT69"));
    FlexGridSizer9->Add(StaticText69, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    Panel2->SetSizer(FlexGridSizer9);
    FlexGridSizer9->Fit(Panel2);
    FlexGridSizer9->SetSizeHints(Panel2);
    Panel3 = new wxPanel(Notebook1, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    FlexGridSizer6 = new wxFlexGridSizer(7, 1, 0, 0);
    GridSizer1 = new wxGridSizer(1, 4, 0, 0);
    FlexGridSizer28 = new wxFlexGridSizer(1, 2, 0, 0);
    StaticText35 = new wxStaticText(Panel3, ID_STATICTEXT35, _(" 0:"), wxDefaultPosition, wxSize(20,-1), wxALIGN_RIGHT, _T("ID_STATICTEXT35"));
    FlexGridSizer28->Add(StaticText35, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl30 = new wxTextCtrl(Panel3, ID_TEXTCTRL30, _("12345"), wxDefaultPosition, wxSize(55,21), wxTE_RIGHT, wxDefaultValidator, _T("ID_TEXTCTRL30"));
    FlexGridSizer28->Add(TextCtrl30, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(FlexGridSizer28, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer29 = new wxFlexGridSizer(1, 2, 0, 0);
    StaticText33 = new wxStaticText(Panel3, ID_STATICTEXT33, _(" 1:"), wxDefaultPosition, wxSize(20,-1), wxALIGN_RIGHT, _T("ID_STATICTEXT33"));
    FlexGridSizer29->Add(StaticText33, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl26 = new wxTextCtrl(Panel3, ID_TEXTCTRL26, _("12345"), wxDefaultPosition, wxSize(55,21), wxTE_RIGHT, wxDefaultValidator, _T("ID_TEXTCTRL26"));
    FlexGridSizer29->Add(TextCtrl26, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(FlexGridSizer29, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer30 = new wxFlexGridSizer(1, 2, 0, 0);
    StaticText36 = new wxStaticText(Panel3, ID_STATICTEXT36, _(" 2:"), wxDefaultPosition, wxSize(20,-1), wxALIGN_RIGHT, _T("ID_STATICTEXT36"));
    FlexGridSizer30->Add(StaticText36, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl27 = new wxTextCtrl(Panel3, ID_TEXTCTRL27, _("12345"), wxDefaultPosition, wxSize(55,21), wxTE_RIGHT, wxDefaultValidator, _T("ID_TEXTCTRL27"));
    FlexGridSizer30->Add(TextCtrl27, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(FlexGridSizer30, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer31 = new wxFlexGridSizer(1, 2, 0, 0);
    StaticText37 = new wxStaticText(Panel3, ID_STATICTEXT37, _(" 3:"), wxDefaultPosition, wxSize(20,-1), wxALIGN_RIGHT, _T("ID_STATICTEXT37"));
    FlexGridSizer31->Add(StaticText37, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl28 = new wxTextCtrl(Panel3, ID_TEXTCTRL28, _("12345"), wxDefaultPosition, wxSize(55,21), wxTE_RIGHT, wxDefaultValidator, _T("ID_TEXTCTRL28"));
    FlexGridSizer31->Add(TextCtrl28, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1->Add(FlexGridSizer31, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer6->Add(GridSizer1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    GridSizer2 = new wxGridSizer(1, 4, 0, 0);
    FlexGridSizer32 = new wxFlexGridSizer(1, 2, 0, 0);
    StaticText38 = new wxStaticText(Panel3, ID_STATICTEXT38, _(" 4:"), wxDefaultPosition, wxSize(20,-1), wxALIGN_RIGHT, _T("ID_STATICTEXT38"));
    FlexGridSizer32->Add(StaticText38, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl29 = new wxTextCtrl(Panel3, ID_TEXTCTRL29, _("12345"), wxDefaultPosition, wxSize(55,21), wxTE_RIGHT, wxDefaultValidator, _T("ID_TEXTCTRL29"));
    FlexGridSizer32->Add(TextCtrl29, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer2->Add(FlexGridSizer32, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer33 = new wxFlexGridSizer(1, 2, 0, 0);
    StaticText39 = new wxStaticText(Panel3, ID_STATICTEXT39, _(" 5:"), wxDefaultPosition, wxSize(20,-1), wxALIGN_RIGHT, _T("ID_STATICTEXT39"));
    FlexGridSizer33->Add(StaticText39, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl31 = new wxTextCtrl(Panel3, ID_TEXTCTRL31, _("12345"), wxDefaultPosition, wxSize(55,21), wxTE_RIGHT, wxDefaultValidator, _T("ID_TEXTCTRL31"));
    FlexGridSizer33->Add(TextCtrl31, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer2->Add(FlexGridSizer33, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer34 = new wxFlexGridSizer(1, 2, 0, 0);
    StaticText40 = new wxStaticText(Panel3, ID_STATICTEXT40, _(" 6:"), wxDefaultPosition, wxSize(20,-1), wxALIGN_RIGHT, _T("ID_STATICTEXT40"));
    FlexGridSizer34->Add(StaticText40, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl32 = new wxTextCtrl(Panel3, ID_TEXTCTRL32, _("12345"), wxDefaultPosition, wxSize(55,21), wxTE_RIGHT, wxDefaultValidator, _T("ID_TEXTCTRL32"));
    FlexGridSizer34->Add(TextCtrl32, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer2->Add(FlexGridSizer34, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer35 = new wxFlexGridSizer(1, 2, 0, 0);
    StaticText41 = new wxStaticText(Panel3, ID_STATICTEXT41, _(" 7:"), wxDefaultPosition, wxSize(20,-1), wxALIGN_RIGHT, _T("ID_STATICTEXT41"));
    FlexGridSizer35->Add(StaticText41, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl33 = new wxTextCtrl(Panel3, ID_TEXTCTRL33, _("12345"), wxDefaultPosition, wxSize(55,21), wxTE_RIGHT, wxDefaultValidator, _T("ID_TEXTCTRL33"));
    FlexGridSizer35->Add(TextCtrl33, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer2->Add(FlexGridSizer35, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer6->Add(GridSizer2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    GridSizer3 = new wxGridSizer(1, 4, 0, 0);
    FlexGridSizer36 = new wxFlexGridSizer(1, 2, 0, 0);
    StaticText42 = new wxStaticText(Panel3, ID_STATICTEXT42, _(" 8:"), wxDefaultPosition, wxSize(20,-1), wxALIGN_RIGHT, _T("ID_STATICTEXT42"));
    FlexGridSizer36->Add(StaticText42, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl34 = new wxTextCtrl(Panel3, ID_TEXTCTRL34, _("12345"), wxDefaultPosition, wxSize(55,21), wxTE_RIGHT, wxDefaultValidator, _T("ID_TEXTCTRL34"));
    FlexGridSizer36->Add(TextCtrl34, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer3->Add(FlexGridSizer36, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer37 = new wxFlexGridSizer(1, 2, 0, 0);
    StaticText43 = new wxStaticText(Panel3, ID_STATICTEXT43, _("9:"), wxDefaultPosition, wxSize(20,-1), wxALIGN_RIGHT, _T("ID_STATICTEXT43"));
    FlexGridSizer37->Add(StaticText43, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl35 = new wxTextCtrl(Panel3, ID_TEXTCTRL35, _("12345"), wxDefaultPosition, wxSize(55,21), wxTE_RIGHT, wxDefaultValidator, _T("ID_TEXTCTRL35"));
    FlexGridSizer37->Add(TextCtrl35, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer3->Add(FlexGridSizer37, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer38 = new wxFlexGridSizer(1, 2, 0, 0);
    StaticText44 = new wxStaticText(Panel3, ID_STATICTEXT44, _("10:"), wxDefaultPosition, wxSize(20,-1), wxALIGN_RIGHT, _T("ID_STATICTEXT44"));
    FlexGridSizer38->Add(StaticText44, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl36 = new wxTextCtrl(Panel3, ID_TEXTCTRL36, _("12345"), wxDefaultPosition, wxSize(55,21), wxTE_RIGHT, wxDefaultValidator, _T("ID_TEXTCTRL36"));
    FlexGridSizer38->Add(TextCtrl36, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer3->Add(FlexGridSizer38, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer39 = new wxFlexGridSizer(1, 2, 0, 0);
    StaticText45 = new wxStaticText(Panel3, ID_STATICTEXT45, _("11:"), wxDefaultPosition, wxSize(20,-1), wxALIGN_RIGHT, _T("ID_STATICTEXT45"));
    FlexGridSizer39->Add(StaticText45, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl37 = new wxTextCtrl(Panel3, ID_TEXTCTRL37, _("12345"), wxDefaultPosition, wxSize(55,21), wxTE_RIGHT, wxDefaultValidator, _T("ID_TEXTCTRL37"));
    FlexGridSizer39->Add(TextCtrl37, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer3->Add(FlexGridSizer39, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer6->Add(GridSizer3, 1, wxTOP|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 7);
    GridSizer4 = new wxGridSizer(1, 4, 0, 0);
    FlexGridSizer40 = new wxFlexGridSizer(1, 2, 0, 0);
    StaticText46 = new wxStaticText(Panel3, ID_STATICTEXT46, _("12:"), wxDefaultPosition, wxSize(20,-1), wxALIGN_RIGHT, _T("ID_STATICTEXT46"));
    FlexGridSizer40->Add(StaticText46, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl38 = new wxTextCtrl(Panel3, ID_TEXTCTRL38, _("12345"), wxDefaultPosition, wxSize(55,21), wxTE_RIGHT, wxDefaultValidator, _T("ID_TEXTCTRL38"));
    FlexGridSizer40->Add(TextCtrl38, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer4->Add(FlexGridSizer40, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer41 = new wxFlexGridSizer(1, 2, 0, 0);
    StaticText47 = new wxStaticText(Panel3, ID_STATICTEXT47, _("13:"), wxDefaultPosition, wxSize(20,-1), wxALIGN_RIGHT, _T("ID_STATICTEXT47"));
    FlexGridSizer41->Add(StaticText47, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl39 = new wxTextCtrl(Panel3, ID_TEXTCTRL39, _("12345"), wxDefaultPosition, wxSize(55,21), wxTE_RIGHT, wxDefaultValidator, _T("ID_TEXTCTRL39"));
    FlexGridSizer41->Add(TextCtrl39, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer4->Add(FlexGridSizer41, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer42 = new wxFlexGridSizer(1, 2, 0, 0);
    StaticText48 = new wxStaticText(Panel3, ID_STATICTEXT48, _("14:"), wxDefaultPosition, wxSize(20,-1), wxALIGN_RIGHT, _T("ID_STATICTEXT48"));
    FlexGridSizer42->Add(StaticText48, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl40 = new wxTextCtrl(Panel3, ID_TEXTCTRL40, _("12345"), wxDefaultPosition, wxSize(55,21), wxTE_RIGHT, wxDefaultValidator, _T("ID_TEXTCTRL40"));
    FlexGridSizer42->Add(TextCtrl40, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer4->Add(FlexGridSizer42, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer43 = new wxFlexGridSizer(1, 2, 0, 0);
    StaticText49 = new wxStaticText(Panel3, ID_STATICTEXT49, _("15:"), wxDefaultPosition, wxSize(20,-1), wxALIGN_RIGHT, _T("ID_STATICTEXT49"));
    FlexGridSizer43->Add(StaticText49, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl41 = new wxTextCtrl(Panel3, ID_TEXTCTRL41, _("12345"), wxDefaultPosition, wxSize(55,21), wxTE_RIGHT, wxDefaultValidator, _T("ID_TEXTCTRL41"));
    FlexGridSizer43->Add(TextCtrl41, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer4->Add(FlexGridSizer43, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer6->Add(GridSizer4, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer44 = new wxFlexGridSizer(8, 1, 0, 0);
    FlexGridSizer46 = new wxFlexGridSizer(1, 5, 0, 0);
    Choice6 = new wxChoice(Panel3, ID_CHOICE6, wxDefaultPosition, wxSize(103,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE6"));
    Choice6->Append(wxEmptyString);
    Choice6->SetSelection( Choice6->Append(_("Dataref int")) );
    Choice6->Append(_("Dataref float"));
    Choice6->Append(_("Array int"));
    Choice6->Append(_("Array float"));
    FlexGridSizer46->Add(Choice6, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText52 = new wxStaticText(Panel3, ID_STATICTEXT52, _("Dataref type"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT52"));
    FlexGridSizer46->Add(StaticText52, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 2);
    FlexGridSizer46->Add(45,9,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 4);
    Choice5 = new wxChoice(Panel3, ID_CHOICE5, wxDefaultPosition, wxSize(48,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE5"));
    Choice5->SetSelection( Choice5->Append(_("0")) );
    Choice5->Append(_("1"));
    Choice5->Append(_("2"));
    Choice5->Append(_("3"));
    Choice5->Append(_("4"));
    Choice5->Append(_("5"));
    Choice5->Append(_("6"));
    Choice5->Append(_("7"));
    Choice5->Append(_("8"));
    Choice5->Append(_("9"));
    Choice5->Append(_("10"));
    Choice5->Append(_("11"));
    Choice5->Append(_("12"));
    Choice5->Append(_("13"));
    Choice5->Append(_("14"));
    Choice5->Append(_("15"));
    Choice5->SetFocus();
    FlexGridSizer46->Add(Choice5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText50 = new wxStaticText(Panel3, ID_STATICTEXT50, _("Axis"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT50"));
    FlexGridSizer46->Add(StaticText50, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    FlexGridSizer44->Add(FlexGridSizer46, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    StaticText53 = new wxStaticText(Panel3, ID_STATICTEXT53, _("Dataref"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT53"));
    FlexGridSizer44->Add(StaticText53, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    TextCtrl42 = new wxTextCtrl(Panel3, ID_TEXTCTRL42, wxEmptyString, wxDefaultPosition, wxSize(359,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL42"));
    FlexGridSizer44->Add(TextCtrl42, 1, wxALL|wxEXPAND, 5);
    FlexGridSizer47 = new wxFlexGridSizer(0, 5, 0, 0);
    StaticText54 = new wxStaticText(Panel3, ID_STATICTEXT54, _("[section name]"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT54"));
    FlexGridSizer47->Add(StaticText54, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 6);
    TextCtrl43 = new wxTextCtrl(Panel3, ID_TEXTCTRL43, wxEmptyString, wxDefaultPosition, wxSize(129,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL43"));
    FlexGridSizer47->Add(TextCtrl43, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 4);
    FlexGridSizer47->Add(41,7,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText59 = new wxStaticText(Panel3, ID_STATICTEXT59, _("Index:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT59"));
    FlexGridSizer47->Add(StaticText59, 1, wxALL|wxALIGN_CENTER_VERTICAL, 1);
    TextCtrl48 = new wxTextCtrl(Panel3, ID_TEXTCTRL48, wxEmptyString, wxDefaultPosition, wxSize(27,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL48"));
    TextCtrl48->Disable();
    FlexGridSizer47->Add(TextCtrl48, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer44->Add(FlexGridSizer47, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer6->Add(FlexGridSizer44, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer45 = new wxFlexGridSizer(1, 3, 0, 0);
    FlexGridSizer45->Add(8,20,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer5 = new wxGridSizer(3, 4, 0, 0);
    Button12 = new wxButton(Panel3, ID_BUTTON12, _("DeviceMax >"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON12"));
    GridSizer5->Add(Button12, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    TextCtrl44 = new wxTextCtrl(Panel3, ID_TEXTCTRL44, wxEmptyString, wxDefaultPosition, wxSize(50,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL44"));
    GridSizer5->Add(TextCtrl44, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 3);
    StaticText65 = new wxStaticText(Panel3, ID_STATICTEXT65, _("SimMax:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT65"));
    GridSizer5->Add(StaticText65, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 1);
    TextCtrl54 = new wxTextCtrl(Panel3, ID_TEXTCTRL54, wxEmptyString, wxDefaultPosition, wxSize(50,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL54"));
    GridSizer5->Add(TextCtrl54, 1, wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    Button13 = new wxButton(Panel3, ID_BUTTON13, _("DevCenter >"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON13"));
    Button13->Disable();
    GridSizer5->Add(Button13, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    TextCtrl52 = new wxTextCtrl(Panel3, ID_TEXTCTRL52, wxEmptyString, wxDefaultPosition, wxSize(50,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL52"));
    TextCtrl52->Disable();
    GridSizer5->Add(TextCtrl52, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 3);
    StaticText66 = new wxStaticText(Panel3, ID_STATICTEXT66, _("SimMin:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT66"));
    GridSizer5->Add(StaticText66, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 1);
    TextCtrl55 = new wxTextCtrl(Panel3, ID_TEXTCTRL55, wxEmptyString, wxDefaultPosition, wxSize(50,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL55"));
    GridSizer5->Add(TextCtrl55, 1, wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    Button14 = new wxButton(Panel3, ID_BUTTON14, _("DeviceMin >"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON14"));
    GridSizer5->Add(Button14, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    TextCtrl53 = new wxTextCtrl(Panel3, ID_TEXTCTRL53, wxEmptyString, wxDefaultPosition, wxSize(50,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL53"));
    GridSizer5->Add(TextCtrl53, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 3);
    StaticText67 = new wxStaticText(Panel3, ID_STATICTEXT67, _("Has center:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXT67"));
    GridSizer5->Add(StaticText67, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 1);
    CheckBox3 = new wxCheckBox(Panel3, ID_CHECKBOX3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
    CheckBox3->SetValue(false);
    GridSizer5->Add(CheckBox3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer45->Add(GridSizer5, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 0);
    FlexGridSizer6->Add(FlexGridSizer45, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    Button10 = new wxButton(Panel3, ID_BUTTON10, _("Add axis section"), wxDefaultPosition, wxSize(148,32), 0, wxDefaultValidator, _T("ID_BUTTON10"));
    FlexGridSizer6->Add(Button10, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel3->SetSizer(FlexGridSizer6);
    FlexGridSizer6->Fit(Panel3);
    FlexGridSizer6->SetSizeHints(Panel3);
    Panel4 = new wxPanel(Notebook1, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL4"));
    FlexGridSizer49 = new wxFlexGridSizer(0, 3, 0, 0);
    Grid1 = new wxGrid(Panel4, ID_GRID1, wxDefaultPosition, wxSize(268,408), 0, _T("ID_GRID1"));
    Grid1->CreateGrid(16,8);
    Grid1->EnableEditing(true);
    Grid1->EnableGridLines(true);
    Grid1->SetColLabelValue(0, _("0"));
    Grid1->SetColLabelValue(1, _("1"));
    Grid1->SetColLabelValue(2, _("2"));
    Grid1->SetColLabelValue(3, _("3"));
    Grid1->SetColLabelValue(4, _("4"));
    Grid1->SetColLabelValue(5, _("5"));
    Grid1->SetColLabelValue(6, _("6"));
    Grid1->SetColLabelValue(7, _("7"));
    Grid1->SetRowLabelValue(0, _("0"));
    Grid1->SetRowLabelValue(1, _("1"));
    Grid1->SetRowLabelValue(2, _("2"));
    Grid1->SetRowLabelValue(3, _("3"));
    Grid1->SetRowLabelValue(4, _("4"));
    Grid1->SetRowLabelValue(5, _("5"));
    Grid1->SetRowLabelValue(6, _("6"));
    Grid1->SetRowLabelValue(7, _("7"));
    Grid1->SetRowLabelValue(8, _("8"));
    Grid1->SetRowLabelValue(9, _("9"));
    Grid1->SetRowLabelValue(10, _("10"));
    Grid1->SetRowLabelValue(11, _("11"));
    Grid1->SetRowLabelValue(12, _("12"));
    Grid1->SetRowLabelValue(13, _("13"));
    Grid1->SetRowLabelValue(14, _("14"));
    Grid1->SetRowLabelValue(15, _("15"));
    Grid1->SetDefaultCellFont( Grid1->GetFont() );
    Grid1->SetDefaultCellTextColour( Grid1->GetForegroundColour() );
    FlexGridSizer49->Add(Grid1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer52 = new wxFlexGridSizer(5, 1, 0, 0);
    FlexGridSizer52->Add(20,244,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button7 = new wxButton(Panel4, ID_BUTTON7, _("Clear outputs"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
    Button7->SetFocus();
    FlexGridSizer52->Add(Button7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer49->Add(FlexGridSizer52, 1, wxALL|wxEXPAND, 5);
    Panel4->SetSizer(FlexGridSizer49);
    FlexGridSizer49->Fit(Panel4);
    FlexGridSizer49->SetSizeHints(Panel4);
    Panel5 = new wxPanel(Notebook1, ID_PANEL5, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL5"));
    FlexGridSizer50 = new wxFlexGridSizer(0, 3, 0, 0);
    Grid2 = new wxGrid(Panel5, ID_GRID2, wxDefaultPosition, wxSize(260,363), 0, _T("ID_GRID2"));
    Grid2->CreateGrid(7,10);
    Grid2->EnableEditing(true);
    Grid2->EnableGridLines(true);
    Grid2->SetColLabelValue(0, _("0"));
    Grid2->SetColLabelValue(1, _("1"));
    Grid2->SetColLabelValue(2, _("2"));
    Grid2->SetColLabelValue(3, _("3"));
    Grid2->SetColLabelValue(4, _("4"));
    Grid2->SetColLabelValue(5, _("5"));
    Grid2->SetColLabelValue(6, _("6"));
    Grid2->SetColLabelValue(7, _("7"));
    Grid2->SetColLabelValue(8, _("8"));
    Grid2->SetColLabelValue(9, _("9"));
    Grid2->SetRowLabelValue(0, _("0"));
    Grid2->SetRowLabelValue(1, _("10"));
    Grid2->SetRowLabelValue(2, _("20"));
    Grid2->SetRowLabelValue(3, _("30"));
    Grid2->SetRowLabelValue(4, _("40"));
    Grid2->SetRowLabelValue(5, _("50"));
    Grid2->SetRowLabelValue(6, _("60"));
    Grid2->SetDefaultCellFont( Grid2->GetFont() );
    Grid2->SetDefaultCellTextColour( Grid2->GetForegroundColour() );
    FlexGridSizer50->Add(Grid2, 1, wxALL|wxEXPAND, 5);
    FlexGridSizer53 = new wxFlexGridSizer(5, 1, 0, 0);
    FlexGridSizer53->Add(20,246,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button11 = new wxButton(Panel5, ID_BUTTON11, _("Clear outputs"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON11"));
    Button11->SetFocus();
    FlexGridSizer53->Add(Button11, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer50->Add(FlexGridSizer53, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel5->SetSizer(FlexGridSizer50);
    FlexGridSizer50->Fit(Panel5);
    FlexGridSizer50->SetSizeHints(Panel5);
    Notebook1->AddPage(Panel1, _("DiscrCtrls"), false);
    Notebook1->AddPage(Panel6, _("NumCtrls"), false);
    Notebook1->AddPage(Panel2, _("Indication"), false);
    Notebook1->AddPage(Panel3, _("Axes"), false);
    Notebook1->AddPage(Panel4, _("AlphNum Indic"), false);
    Notebook1->AddPage(Panel5, _("Discrete Indic"), false);
    FlexGridSizer3->Add(Notebook1, 1, wxALL|wxEXPAND, 5);
    FlexGridSizer59 = new wxFlexGridSizer(1, 0, 0, 0);
    ComboBox3 = new wxComboBox(this, ID_COMBOBOX3, wxEmptyString, wxDefaultPosition, wxSize(78,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX3"));
    ComboBox3->SetSelection( ComboBox3->Append(_("128")) );
    ComboBox3->Append(_("48"));
    ComboBox3->Append(_("96"));
    ComboBox3->Append(_("144"));
    ComboBox3->Append(_("192"));
    ComboBox3->Append(_("240"));
    ComboBox3->Append(_("288"));
    ComboBox3->Append(_("336"));
    ComboBox3->Append(_("384"));
    FlexGridSizer59->Add(ComboBox3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText70 = new wxStaticText(this, ID_STATICTEXT70, _("Numeric\nmemory size"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT70"));
    FlexGridSizer59->Add(StaticText70, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button24 = new wxButton(this, ID_BUTTON24, _("ClearAll"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON24"));
    FlexGridSizer59->Add(Button24, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ComboBox4 = new wxComboBox(this, ID_COMBOBOX4, wxEmptyString, wxDefaultPosition, wxSize(72,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX4"));
    ComboBox4->SetSelection( ComboBox4->Append(_("64")) );
    ComboBox4->Append(_("128"));
    ComboBox4->Append(_("256"));
    ComboBox4->Append(_("384"));
    ComboBox4->Append(_("512"));
    ComboBox4->Append(_("640"));
    ComboBox4->Append(_("768"));
    ComboBox4->Append(_("896"));
    ComboBox4->Append(_("1024"));
    FlexGridSizer59->Add(ComboBox4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText71 = new wxStaticText(this, ID_STATICTEXT71, _("Discrete\nmemory size"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT71"));
    FlexGridSizer59->Add(StaticText71, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(FlexGridSizer59, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2->Add(FlexGridSizer3, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 0);
    StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL, _T("ID_STATICLINE1"));
    FlexGridSizer2->Add(StaticLine1, 1, wxALL|wxEXPAND, 0);
    FlexGridSizer15 = new wxFlexGridSizer(11, 1, 0, 0);
    FlexGridSizer26 = new wxFlexGridSizer(40, 1, 0, 0);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Device"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    wxFont StaticText1Font(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    StaticText1->SetFont(StaticText1Font);
    FlexGridSizer26->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
    TextCtrl22 = new wxTextCtrl(this, ID_TEXTCTRL22, wxEmptyString, wxDefaultPosition, wxSize(32,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL22"));
    FlexGridSizer26->Add(TextCtrl22, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Disconnected"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    wxFont StaticText2Font(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText2->SetFont(StaticText2Font);
    FlexGridSizer26->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    StaticLine7 = new wxStaticLine(this, ID_STATICLINE7, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE7"));
    FlexGridSizer26->Add(StaticLine7, 1, wxALL|wxEXPAND, 0);
    StaticText24 = new wxStaticText(this, ID_STATICTEXT24, _("Serial port"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT24"));
    wxFont StaticText24Font(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    StaticText24->SetFont(StaticText24Font);
    FlexGridSizer26->Add(StaticText24, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button4 = new wxButton(this, ID_BUTTON4, _("Refresh list"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    FlexGridSizer26->Add(Button4, 1, wxALL|wxEXPAND, 1);
    ComboBox1 = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxSize(69,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
    FlexGridSizer26->Add(ComboBox1, 1, wxALL|wxEXPAND, 1);
    StaticText51 = new wxStaticText(this, ID_STATICTEXT51, _("Baudrate"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT51"));
    FlexGridSizer26->Add(StaticText51, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    ComboBox2 = new wxComboBox(this, ID_COMBOBOX2, wxEmptyString, wxDefaultPosition, wxSize(79,21), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX2"));
    ComboBox2->Append(_("9600"));
    ComboBox2->Append(_("19200"));
    ComboBox2->Append(_("38400"));
    ComboBox2->Append(_("57600"));
    ComboBox2->SetSelection( ComboBox2->Append(_("115200")) );
    ComboBox2->Disable();
    FlexGridSizer26->Add(ComboBox2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button1 = new wxButton(this, ID_BUTTON1, _("Open"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    FlexGridSizer26->Add(Button1, 1, wxALL|wxEXPAND, 1);
    Button8 = new wxButton(this, ID_BUTTON8, _("Reset (Arduino)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON8"));
    FlexGridSizer26->Add(Button8, 1, wxALL|wxEXPAND, 1);
    Button2 = new wxButton(this, ID_BUTTON2, _("Close"), wxDefaultPosition, wxSize(62,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    Button2->Disable();
    FlexGridSizer26->Add(Button2, 1, wxALL|wxEXPAND, 1);
    FlexGridSizer26->Add(91,12,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticLine8 = new wxStaticLine(this, ID_STATICLINE8, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE8"));
    FlexGridSizer26->Add(StaticLine8, 1, wxALL|wxEXPAND, 0);
    StaticText55 = new wxStaticText(this, ID_STATICTEXT55, _("UDP server"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT55"));
    wxFont StaticText55Font(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText55->SetFont(StaticText55Font);
    FlexGridSizer26->Add(StaticText55, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer55 = new wxFlexGridSizer(0, 3, 0, 0);
    StaticText32 = new wxStaticText(this, ID_STATICTEXT32, _("UDP port"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT32"));
    wxFont StaticText32Font(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    StaticText32->SetFont(StaticText32Font);
    FlexGridSizer55->Add(StaticText32, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl47 = new wxTextCtrl(this, ID_TEXTCTRL47, _("12345"), wxDefaultPosition, wxSize(47,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL47"));
    FlexGridSizer55->Add(TextCtrl47, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer26->Add(FlexGridSizer55, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer58 = new wxFlexGridSizer(0, 3, 0, 0);
    Button22 = new wxButton(this, ID_BUTTON22, _("Start"), wxDefaultPosition, wxSize(52,23), 0, wxDefaultValidator, _T("ID_BUTTON22"));
    FlexGridSizer58->Add(Button22, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button23 = new wxButton(this, ID_BUTTON23, _("Stop"), wxDefaultPosition, wxSize(49,23), 0, wxDefaultValidator, _T("ID_BUTTON23"));
    FlexGridSizer58->Add(Button23, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer26->Add(FlexGridSizer58, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    StaticLine9 = new wxStaticLine(this, ID_STATICLINE9, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE9"));
    FlexGridSizer26->Add(StaticLine9, 1, wxALL|wxEXPAND, 0);
    FlexGridSizer26->Add(91,28,1, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticLine10 = new wxStaticLine(this, ID_STATICLINE10, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE10"));
    FlexGridSizer26->Add(StaticLine10, 1, wxALL|wxEXPAND, 0);
    StaticText30 = new wxStaticText(this, ID_STATICTEXT30, _("Console"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT30"));
    wxFont StaticText30Font(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    StaticText30->SetFont(StaticText30Font);
    FlexGridSizer26->Add(StaticText30, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    Button9 = new wxButton(this, ID_BUTTON9, _("Console ON/OFF"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON9"));
    FlexGridSizer26->Add(Button9, 1, wxALL|wxEXPAND, 5);
    CheckBox2 = new wxCheckBox(this, ID_CHECKBOX2, _("Inputs only"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    CheckBox2->SetValue(false);
    CheckBox2->Disable();
    FlexGridSizer26->Add(CheckBox2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticLine6 = new wxStaticLine(this, ID_STATICLINE6, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE6"));
    FlexGridSizer26->Add(StaticLine6, 1, wxTOP|wxBOTTOM|wxEXPAND, 4);
    FlexGridSizer26->Add(91,8,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button3 = new wxButton(this, ID_BUTTON3, _("Quit"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    FlexGridSizer26->Add(Button3, 1, wxALL|wxEXPAND, 1);
    FlexGridSizer15->Add(FlexGridSizer26, 1, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 8);
    FlexGridSizer2->Add(FlexGridSizer15, 1, wxALL|wxEXPAND, 0);
    FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxEXPAND, 0);
    SetSizer(FlexGridSizer1);
    Timer1.SetOwner(this, ID_TIMER1);
    Timer1.Start(20, false);
    Timer2.SetOwner(this, ID_TIMER2);
    Timer2.Start(999999, true);
    FlexGridSizer1->Fit(this);
    FlexGridSizer1->SetSizeHints(this);

    Connect(ID_CHOICE2,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&loggerDialog::OnChoice2Select);
    Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&loggerDialog::OnChoice1Select1);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&loggerDialog::OnButton5Click);
    Connect(ID_CHOICE7,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&loggerDialog::OnChoice7Select);
    Connect(ID_BUTTON18,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&loggerDialog::OnButton18Click);
    Connect(ID_BUTTON19,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&loggerDialog::OnButton19Click);
    Connect(ID_BUTTON20,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&loggerDialog::OnButton20Click);
    Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&loggerDialog::OnCheckBox4Click);
    Connect(ID_BUTTON21,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&loggerDialog::OnButton21Click);
    Panel6->Connect(wxEVT_PAINT,(wxObjectEventFunction)&loggerDialog::OnPanel6Paint,0,this);
    Panel6->Connect(wxEVT_ENTER_WINDOW,(wxObjectEventFunction)&loggerDialog::OnPanel6MouseEnter,0,this);
    Connect(ID_CHOICE4,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&loggerDialog::OnChoice4Select);
    Connect(ID_CHOICE3,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&loggerDialog::OnChoice3Select);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&loggerDialog::OnButton6Click);
    Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&loggerDialog::OnCheckBox1Click);
    Connect(ID_BUTTON15,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&loggerDialog::OnButton15Click);
    Connect(ID_BUTTON16,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&loggerDialog::OnButton16Click);
    Connect(ID_BUTTON17,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&loggerDialog::OnButton17Click);
    Connect(ID_CHOICE6,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&loggerDialog::OnChoice6Select);
    Connect(ID_CHOICE5,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&loggerDialog::OnChoice5Select);
    Connect(ID_BUTTON12,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&loggerDialog::OnButton12Click);
    Connect(ID_BUTTON13,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&loggerDialog::OnButton13Click);
    Connect(ID_BUTTON14,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&loggerDialog::OnButton14Click);
    Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&loggerDialog::OnCheckBox3Click);
    Connect(ID_BUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&loggerDialog::OnButton10Click2);
    Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&loggerDialog::OnButton7Click);
    Connect(ID_BUTTON11,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&loggerDialog::OnButton7Click);
    Connect(ID_NOTEBOOK1,wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED,(wxObjectEventFunction)&loggerDialog::OnNotebook1PageChanged);
    Connect(ID_COMBOBOX3,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&loggerDialog::OnComboBox3Selected);
    Connect(ID_BUTTON24,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&loggerDialog::OnButton24Click);
    Connect(ID_COMBOBOX4,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&loggerDialog::OnComboBox4Selected);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&loggerDialog::OnButton4Click);
    Connect(ID_COMBOBOX1,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&loggerDialog::OnComboBox1Selected);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&loggerDialog::OnButton1Click);
    Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&loggerDialog::OnButton8Click);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&loggerDialog::OnButton2Click);
    Connect(ID_BUTTON22,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&loggerDialog::OnButton22Click);
    Connect(ID_BUTTON23,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&loggerDialog::OnButton23Click);
    Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&loggerDialog::OnButton9Click1);
    Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&loggerDialog::OnCheckBox2Click);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&loggerDialog::OnButton3Click);
    Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&loggerDialog::OnTimer1Trigger);
    Connect(ID_TIMER2,wxEVT_TIMER,(wxObjectEventFunction)&loggerDialog::OnTimer2Trigger);
    //*)

    axes[0] = TextCtrl30;
    axes[1] = TextCtrl26;
    axes[2] = TextCtrl27;
    axes[3] = TextCtrl28;
    axes[4] = TextCtrl29;
    axes[5] = TextCtrl31;
    axes[6] = TextCtrl32;
    axes[7] = TextCtrl33;
    axes[8] = TextCtrl34;
    axes[9] = TextCtrl35;
    axes[10] = TextCtrl36;
    axes[11] = TextCtrl37;
    axes[12] = TextCtrl38;
    axes[13] = TextCtrl39;
    axes[14] = TextCtrl40;
    axes[15] = TextCtrl41;


    SetTitle("Config helper 0.3.2 - extended IO edition");
    StaticText2->SetForegroundColour(clDarkYellow);
    connection_flag = 0;
    connection_timer = 0;
    StaticText2->SetLabel("Disconnected");
    LoadPortsList();
    get_config();
    logger_dialog = this;
    controls_params_selector();
    indication_params_selector();
    memset(display_array,' ',sizeof(display_array));
    memset(led_array,'0',sizeof(led_array));
    Button8->Enable(false);
    Timer2.Stop();
    console_flag = 0;
    Choice5->SetSelection(0);

    Grid1->AutoSizeColumns(true);
    Grid2->AutoSizeColumns(true);

    wxFont fnt;
    fnt.MakeBold();
    axes[0]->SetForegroundColour(wxColor(255,255,255));
    axes[0]->SetBackgroundColour(wxColor(0,0,0));
    axes[0]->SetFont(fnt);
    Notebook1->Refresh();
    udp_server.SetCallback((void*)udp_call_back);
}

loggerDialog::~loggerDialog()
{
    //(*Destroy(loggerDialog)
    //*)
}


int loggerDialog::get_config(void)
{
    wxConfig *config = new wxConfig(__CONFIG_NAME__);
    wxString tmp;

    tmp = config->Read("SerialPort", "Select port");
    ComboBox1->SetValue(tmp);

    tmp = config->Read("BaudRate", "115200");
    ComboBox2->SetValue(tmp);

    delete config;
}


int loggerDialog::put_config(void)
{
    wxString tmp;
    wxConfig *config = new wxConfig(__CONFIG_NAME__);
    config->Write("SerialPort", ComboBox1->GetValue());
    config->Write("BaudRate", ComboBox2->GetValue());
    delete config;
}

int loggerDialog::GetMaxLen(wxTextCtrl *ed)
{
    int len_max = 0,
        i,
        cur_len,
        lines_number = ed->GetNumberOfLines();

    for(i = 0; i < lines_number; i++)
    {
        cur_len = ed->GetLineText(i).Len();
        if(cur_len > len_max)
            len_max = cur_len;

    }

    return len_max;
}


void loggerDialog::OnQuit(wxCommandEvent& event)
{
    put_config();
    serial_port.Close();
    Close();
}

void loggerDialog::OnAbout(wxCommandEvent& event)
{
    //s.SetCallback((void*)rx_call_back);
    //s.Open("COM10",115200);
    //wxString msg = wxbuildinfo(long_f);
    //wxMessageBox(msg, _("Welcome to..."));
}

void loggerDialog::OnButton3Click(wxCommandEvent& event)
{
    if(timer_enabled)
    {
        put_config();
        serial_port.Close();
        printf("Port %s closed\n",(char*)ComboBox1->GetValue().c_str().AsChar());
    }

    printf("Program closed\n");
    Close();
}

void loggerDialog::LoadPortsList(void)
{
    char buf[2048];
    char cur_line[100],*p,*s;
    int cnt,i,line_cnt;
    wxString tmp;
    ComboBox1->Clear();
    cnt = get_port_list(buf);
    if(cnt)
    {
        p = buf;
        s = cur_line;
        for(i=0; i<strlen(buf); i++)
        {
            if(*p == '\r')
            {
                continue;
            }
            else if(*p == '\n')
            {
                *s = 0;
                tmp.Printf("%s",cur_line);
                ComboBox1->Append(_(tmp));
                s = cur_line;
            }
            else
                *s++ = *p;

            p++;
        }

    }
}


void loggerDialog::OnChoice1Select(wxCommandEvent& event)
{
    //get_port_list(NULL);
}

void loggerDialog::OnButton4Click(wxCommandEvent& event)
{
    LoadPortsList();
}

void loggerDialog::OnButton1Click(wxCommandEvent& event)
{
    StaticText2->SetForegroundColour(clDarkYellow);
    StaticText2->SetLabel("Disconnected");
    SetInactive(0);
    SetInactive(1);
    SetInactive(2);
    SetInactive(3);
    SetInactive(-1);

    serial_port.SetCallback((void*)rx_call_back);
    long baudrate;
    ComboBox2->GetValue().ToLong(&baudrate);
    if(serial_port.Open(ComboBox1->GetValue().c_str(),baudrate))
    {
        timer_enabled = 50;
        put_config();
        Button1->Enable(false);
        Button2->Enable(true);
        Button8->Enable(true);
        ComboBox1->Enable(false);
        set_text_color(BRIGHT_GREEN);
        printf("Port %s opened at %d\n",(char*)ComboBox1->GetValue().c_str().AsChar(),baudrate);
        set_text_color(WHITE);
    }
    else
    {
        set_text_color(BRIGHT_RED);
        printf("Could not open port %s\n",(char*)ComboBox1->GetValue().c_str().AsChar());
        set_text_color(WHITE);
    }



}

void loggerDialog::OnButton2Click(wxCommandEvent& event)
{
    StaticText2->SetForegroundColour(clDarkYellow);
    StaticText2->SetLabel("Disconnected");
    timer_enabled = 0;
    Button2->Enable(false);
    Button1->Enable(true);
    Button8->Enable(false);
    ComboBox1->Enable(true);

    serial_port.Close();
    SetInactive(0);
    SetInactive(1);
    SetInactive(2);
    SetInactive(3);
    SetInactive(-1);
    printf("Port %s closed\n",(char*)ComboBox1->GetValue().c_str().AsChar());

}

static unsigned char nibble(int hex)
{
    if(hex>='0' && hex<='9')
        return (hex - '0');
    if(hex>='A' && hex<='F')
        return (hex - 'A' + 10);
    if(hex>='a' && hex<='f')
        return (hex - 'a' + 10);
    return 0;
}

static int hex2int(char *hh)
{
    int nib1 = nibble(hh[0]&0xFF);
    int nib2 = nibble(hh[1]&0xFF);
    return  (nib1 << 4) + nib2;
}



wxColour get_status(char *line, int curr_cass)
{
    wxColour cl;
    char bt[3];
    int state;
    char *p = strstr(line,"data: [");
    if(p == NULL)
        return -1;

    p += strlen("data: [");
    state =hex2int(p) & 1;

    switch(state)
    {
    case 0:
        cl = clRed;
        //if(cd[curr_cass].alarm_sensor == 0)
        //{
        //    cd[curr_cass].alarm_sensor = 1;
        //    log_write("Cassette %d alarm sensor in signaled state", curr_cass + 1);
        //}
        break;


    case 1:
        cl = clLime;
        break;
    default:
        cl = clGray;
    }
    return cl;
}


void loggerDialog::SetInactive(int curr_cass)
{


}

void loggerDialog::SetCommLedColor(int curr_cass, int com_state,
                                   wxStaticText *st1,
                                   wxStaticText *st2,
                                   wxStaticText *st3,
                                   wxStaticText *st4
                                  )
{

    wxColour cl;
    if(com_state)
        cl = clLime;
    else
        cl = clRed;

    switch(curr_cass)
    {
    case 0:
        st1->SetBackgroundColour(cl);
        st1->SetLabel(" ");
        break;
    case 1:
        st2->SetBackgroundColour(cl);
        st2->SetLabel(" ");
        break;
    case 2:
        st3->SetBackgroundColour(cl);
        st3->SetLabel(" ");
        break;
    case 3:
        st4->SetBackgroundColour(cl);
        st4->SetLabel(" ");
        break;

    }


}



void loggerDialog::put_text_data(int curr_cassette, wxString str,
                                 wxStaticText *st1,
                                 wxStaticText *st2,
                                 wxStaticText *st3,
                                 wxStaticText *st4
                                )
{
    switch(curr_cassette)
    {
    case 0:
        st1->SetLabel(str);
        break;
    case 1:
        st2->SetLabel(str);
        break;
    case 2:
        st3->SetLabel(str);
        break;
    case 3:
        st4->SetLabel(str);
        break;
    }

}


int udp_call_back(char *rxbuf, int rxlen)
{



    return 0;
}

unsigned long event2hex(const char *in)
{
unsigned long result  = 0;
  sscanf(in,"%X",&result);
  return result;
}

int rx_call_back(char *rxbuf, int rxlen)
{
    static char app_buf[2000];
    //char id_txt[8], val_txt[8];
    static int current_ndx = 0;
    //int dev,id,val;
    long ev_filter;
    wxString tmp;
    int pars_cnt;
    char tmpstr[10];
    unsigned long event;
    ULONG64 ev_container;
    EVENT_STRUCT *ev = (EVENT_STRUCT*)&ev_container;


#ifdef PARANOIC_TEST
    printf("C");
#endif
    int i;
    for(i=0; i<rxlen; i++)
    {
        if(rxlen)
        {
            for(i=0; i<rxlen; i++)
            {

                switch(rxbuf[i])
                {

                case '!':
                    if(!logger_dialog->CheckBox2->IsChecked())
                    {
                        printf("\nACK\n");
                    }
                    break;

                case '{':
                    current_ndx = 0;

                    break;

                case '}':

          app_buf[current_ndx] = 0x00;

           switch(current_ndx)
           {
              case 3:  /* 801 */
                 event = event2hex(app_buf);
                 ev->event_type =  event >> 8;
                 ev->event_id = event & 0xFF;
                 //ev->port_id = sws->port_id;
                 ev->value = 0;
              break;

              case 4:   /* 8001*/
                 event = event2hex(app_buf);
                 ev->event_type =  event >> 12;
                 ev->event_id = event & 0xFFF;
                 //ev->port_id = sws->port_id;
                 ev->value = 0;
              break;

              case 7: /* A011234*/
                 //app_buf[7] = '0';
                 //app_buf[7] = 0x00;
                 event = event2hex(app_buf);
                 //event >>= 4;
                 ev->event_type =  event >> 24;
                 ev->event_id = (event >> 16) & 0xFF;
                 //ev->port_id = sws->port_id;
                 ev->value = event & 0xFFFF;
              break;

              case 8:  /* A0011234*/
                 event = event2hex(app_buf);
                 ev->event_type =  event >> 28;
                 ev->event_id = (event >> 16) & 0xFFF;
                 //ev->port_id = sws->port_id;
                 ev->value = event & 0xFFFF;
              break;

           }

                    logger_dialog->StaticText2->SetForegroundColour(clDarkGreen);
                    logger_dialog->StaticText2->SetLabel("Connected");
                    logger_dialog->connection_timer = 0;
                    logger_dialog->connection_flag = 1;

                    if(ev->event_type == 0x0F)
                    {
                        tmp.Printf("%d",ev->event_id);
                        logger_dialog->TextCtrl22->SetValue(tmp);
                        if(!logger_dialog->CheckBox2->IsChecked())
                        {
                            set_text_color(BRIGHT_MAGENTA);
                            printf("Device detect response: {%s}\n",app_buf);
                            set_text_color(WHITE);
                        }
                    }
                    else
                    {
                        if(current_panel == 0 && ev->event_type != 0x0A)
                        {
                            set_text_color(BRIGHT_YELLOW);
                            printf("{%s}  %d\n",app_buf,ev->event_id);
                            set_text_color(WHITE);

                            tmp.Printf("%d",ev->event_id);
                            logger_dialog->TextCtrl10->SetValue(tmp);
                            tmp.Printf("{%s}",app_buf);
                            logger_dialog->TextCtrl25->SetValue(tmp);
                        }
                        #if 0
                        if(current_panel == 1 && ev->event_type == 0x0A)
                        {
                            set_text_color(BRIGHT_YELLOW);
                            printf("{%s}  %d   %d\n",app_buf, ev->event_id, ev->value);
                            set_text_color(WHITE);

                            logger_dialog->TextCtrl61->GetValue().ToLong(&ev_filter);
                            tmp.Printf("%d",ev->event_id);
                            logger_dialog->TextCtrl60->SetValue(tmp);
                            tmp.Printf("{%s}",app_buf);
                            logger_dialog->TextCtrl59->SetValue(tmp);

                            if(logger_dialog->TextCtrl61->GetValue().Len() > 0)
                            {
                                if(ev->event_id == ev_filter)
                                {
                                    tmp.Printf("%d",ev->value);
                                    logger_dialog->TextCtrl62->SetValue(tmp);
                                }
                                else
                                {
                                    tmp.Printf("%d",ev->value);
                                    logger_dialog->TextCtrl62->SetValue("-----");
                                }

                            }
                            else
                            {
                                tmp.Printf("%d",ev->value);
                                logger_dialog->TextCtrl62->SetValue(tmp);
                            }
                        }
                        #endif
                    }

            break;

                default:
                    if(current_ndx<1000)
                    {
                        app_buf[current_ndx++] = rxbuf[i];
                    }


                }
            }
        }
    }
#ifdef PARANOIC_TEST
    printf("c");
#endif
    return 0;
}



int rx_call_back_______(char *rxbuf, int rxlen)
{
    static char app_buf[2000];
    char id_txt[8], val_txt[8];
    static int current_ndx = 0;
    int dev,id,val;
    long ev_filter;
    wxString tmp;
    int pars_cnt;
    char tmpstr[10];
    unsigned long event;
    ULONG64 ev_container;
    EVENT_STRUCT *ev = (EVENT_STRUCT*)&ev_container;
#ifdef PARANOIC_TEST
    printf("C");
#endif
    int i;
    for(i=0; i<rxlen; i++)
    {
        if(rxlen)
        {
            for(i=0; i<rxlen; i++)
            {

                switch(rxbuf[i])
                {

                case '!':
                   if(!logger_dialog->CheckBox2->IsChecked())
                   {
                       printf("\nACK\n");
                   }
                    break;

                case '{':
                    current_ndx = 0;

                    break;

                case '}':
                    //финализация работы с пакетом
           app_buf[current_ndx] = 0x00;

           switch(current_ndx)
           {
              case 3:  /* 801 */
                 event = event2hex(app_buf);
                 ev->event_type =  event >> 8;
                 ev->event_id = event & 0xFF;
                 //ev->port_id = sws->port_id;
                 ev->value = 0;
              break;

              case 4:   /* 8001*/
                 event = event2hex(app_buf);
                 ev->event_type =  event >> 12;
                 ev->event_id = event & 0xFFF;
                 //ev->port_id = sws->port_id;
                 ev->value = 0;
              break;

              case 7: /* A011234*/
                 //app_buf[7] = '0';
                 //app_buf[7] = 0x00;
                 event = event2hex(app_buf);
                 //event >>= 4;
                 ev->event_type =  event >> 24;
                 ev->event_id = (event >> 16) & 0xFF;
                 //ev->port_id = sws->port_id;
                 ev->value = event & 0xFFFF;
              break;

              case 8:  /* A0011234*/
                 event = event2hex(app_buf);
                 ev->event_type =  event >> 28;
                 ev->event_id = (event >> 16) & 0xFFF;
                 //ev->port_id = sws->port_id;
                 ev->value = event & 0xFFFF;
              break;

           }
                    logger_dialog->StaticText2->SetForegroundColour(clDarkGreen);
                    logger_dialog->StaticText2->SetLabel("Connected");
                    logger_dialog->connection_timer = 0;
                    logger_dialog->connection_flag = 1;

                    memcpy(id_txt,app_buf,3);
                    id_txt[3] = 0;
                    sscanf(id_txt,"%x",&id);

                    if(strlen(app_buf) == 7)
                    {
                       memcpy(val_txt,&app_buf[3],4);
                       val_txt[4] = 0;
                       sscanf(val_txt,"%x",&val);
                    }
                    else
                        val_txt[4] = 0;

                    dev = id & 0xF00;
                    id &= 0xFF;
                    tmp.Printf("%d",id);
                    if(dev == 0xF00 )
                    {
                        logger_dialog->TextCtrl22->SetValue(tmp);
                        if(!logger_dialog->CheckBox2->IsChecked())
                        {
                            set_text_color(BRIGHT_MAGENTA);
                            printf("Device detect response: {%s}\n",app_buf);
                            set_text_color(WHITE);
                        }
                    }
                    else
                    {
                        if(current_panel == 0 && dev != 0xA00)
                        {
                           set_text_color(BRIGHT_YELLOW);
                           printf("{%s}  %d\n",app_buf,id);
                           set_text_color(WHITE);

                           tmp.Printf("%d",id);
                           logger_dialog->TextCtrl10->SetValue(tmp);
                           tmp.Printf("{%s}",app_buf);
                           logger_dialog->TextCtrl25->SetValue(tmp);
                        }
                        if(current_panel == 1 && dev == 0xA00)
                        {
                           set_text_color(BRIGHT_YELLOW);
                           printf("{%s}  %d   %d\n",app_buf, id, val);
                           set_text_color(WHITE);

                           logger_dialog->TextCtrl61->GetValue().ToLong(&ev_filter);
                           tmp.Printf("%d",id);
                           logger_dialog->TextCtrl60->SetValue(tmp);
                           tmp.Printf("{%s}",app_buf);
                           logger_dialog->TextCtrl59->SetValue(tmp);

                           if(logger_dialog->TextCtrl61->GetValue().Len() > 0)
                           {
                             if(id == ev_filter)
                             {
                               tmp.Printf("%d",val);
                               logger_dialog->TextCtrl62->SetValue(tmp);
                             }
                             else
                             {
                               tmp.Printf("%d",val);
                               logger_dialog->TextCtrl62->SetValue("-----");
                             }

                           }
                           else
                           {
                               tmp.Printf("%d",val);
                               logger_dialog->TextCtrl62->SetValue(tmp);
                           }
                        }
                    }

                    break;

                default:
                    if(current_ndx<1000)
                    {
                        app_buf[current_ndx++] = rxbuf[i];
                    }


                }
            }
        }
    }
#ifdef PARANOIC_TEST
    printf("c");
#endif
    return 0;
}

int min_(int x, int y)
{
    if(x>y)
        return y;
    return x;
}
#if 0
void loggerDialog::OnTimer1Trigger(wxTimerEvent& event)
{
    static int state = 0;
    int i,res = 0;
    wxString output_tmp;
    char tmp_array[256],*ptmp_array;
    long device,position,length,index,factor,offset,mask,options,dataref_type,indication_type;

     long numeric_tape_len;
     ComboBox3->GetValue().ToLong(&numeric_tape_len);
     long discrete_tape_len;
     ComboBox4->GetValue().ToLong(&discrete_tape_len);
     discrete_tape_len *= 8;
     int devs = numeric_tape_len / 8;



    if(timer_enabled == 0)
        return;

    if(timer_enabled > 1)
    {
        timer_enabled--;
        return;
    }
#ifdef PARANOIC_TEST
    printf("T");
#endif
    if(!TextCtrl14->GetValue().ToLong(&device))
        device = 0;

    if(!TextCtrl15->GetValue().ToLong(&position))
        position = 0;
    if(!TextCtrl16->GetValue().ToLong(&length))
        length = 0;
    if(!TextCtrl21->GetValue().ToLong(&index))
        index = 0;
    if(!TextCtrl18->GetValue().ToLong(&factor))
        factor = 0;
    if(!TextCtrl19->GetValue().ToLong(&offset))
        offset = 0;
    if(!TextCtrl20->GetValue().ToLong(&mask))
        mask = 0;
    options = 0;
    if(CheckBox1->IsChecked())
        options += 1;

    indication_type =  Choice4->GetSelection();
    dataref_type = Choice3->GetSelection();
    wxString tmpwxstr = TextCtrl12->GetValue();
    const char *data = tmpwxstr.c_str().AsChar();
    int data_len = strlen(data);
    data_len = min_(length,data_len);



    switch(indication_type)
    {
    case NUMERIC:
        if(device >=0 && device < 16 && position >=0 && position <8 && data_len > 0 && data_len <= 8)
            memcpy(&display_array[4+8*(/*(devs-1)-*/device) + position],data,data_len);
        break;

    case DISCRETE:
        int value = atoi(data);
        if(position >=0 && position < 1024)
            led_array[position+4] = '0' + (value & 1);
        break;
    }


#if 1
    //ComboBox3->GetValue().ToLong(&val);

    switch(++state)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 9:

    case 2:
    case 4:
    case 6:
    case 8:



        if(current_panel == 2 || current_panel == 4)
        ;
        else
            break;

        display_array[0] = '{';
        display_array[1] = '7';
        display_array[2] = 'S';
        display_array[3] = 'G';
        display_array[numeric_tape_len + 4] = '}';
        display_array[numeric_tape_len + 5] = 0;



        res = serial_port.SerialWrite((unsigned char*)display_array, sizeof(display_array));




        //break;


        if(current_panel == 2 || current_panel == 5)
        ;
        else
            break;

        led_array[0] = '{';
        led_array[1] = 'L';
        led_array[2] = 'E';
        led_array[3] = 'D';
        led_array[discrete_tape_len+4] = '}';
        led_array[discrete_tape_len+5] = 0;

        //for(i=0,ptmp_array = tmp_array; i < 36; i++)
        //    *ptmp_array++ = led_array[i];
        //*ptmp_array++ = '\r';
        //*ptmp_array++ = '\n';
        //
        //for(; i< 70; i++)
        //{
        //    *ptmp_array++ = led_array[i];
        //}



        //for(i=0; i< 64; i++)
        //{
        //    wxString tmp;
        //    tmp.Printf("%c",'0' + (led_array[i+4] & 1));
        //    Grid2->SetCellValue(tmp, i/10, i%10);
        //}


        //output_tmp.Printf("%s",tmp_array);
        res = serial_port.SerialWrite((unsigned char*)led_array, sizeof(led_array));
        //printf("L");
        //if(!CheckBox2->IsChecked())
        //{
        //    set_text_color(BRIGHT_CYAN);
        //    printf("%s\n",led_array);
        //    set_text_color(WHITE);
        //}
        break;
    case 10:
#ifdef PARANOIC_TEST
        printf("D");
#endif
        //if(current_panel != 0)
        //    break;
        res = serial_port.SerialWrite((unsigned char*)"{DET}", 5);
        if(!CheckBox2->IsChecked())
        {
            set_text_color(BRIGHT_CYAN);
            printf("{DET}\n");
            set_text_color(BRIGHT_WHITE);
        }
        state = 0;
    }


#endif
    if(res == -1)
    {
        connection_flag = 0;
        StaticText2->SetForegroundColour(clRed);
        StaticText2->SetLabel("Comm.Error");

    }
    else
    if(++connection_timer == 20)
    {
        connection_flag = 0;
        StaticText2->SetForegroundColour(clDarkYellow);
        StaticText2->SetLabel("Disconnected");
    }
#ifdef PARANOIC_TEST
    printf("t");
#endif
}
#endif
void loggerDialog::OnTimer1Trigger(wxTimerEvent& event)
{
    static int state = 0;
    int i,res = 0;
    wxString output_tmp;
    char tmp_array[256],*ptmp_array;
    long device,position,length,index,factor,offset,mask,options,dataref_type,indication_type;

     long numeric_tape_len;
     ComboBox3->GetValue().ToLong(&numeric_tape_len);
     long discrete_tape_len;
     ComboBox4->GetValue().ToLong(&discrete_tape_len);
     //discrete_tape_len *= 8;
     int devs = numeric_tape_len / 8;


    if(timer_enabled == 0)
        return;

    if(timer_enabled > 1)
    {
        timer_enabled--;
        return;
    }
#ifdef PARANOIC_TEST
    printf("T");
#endif
    if(!TextCtrl14->GetValue().ToLong(&device))
        device = 0;

    if(!TextCtrl15->GetValue().ToLong(&position))
        position = 0;
    if(!TextCtrl16->GetValue().ToLong(&length))
        length = 0;
//    if(!TextCtrl21->GetValue().ToLong(&index))
//        index = 0;
    if(!TextCtrl18->GetValue().ToLong(&factor))
        factor = 0;
    if(!TextCtrl19->GetValue().ToLong(&offset))
        offset = 0;
    if(!TextCtrl20->GetValue().ToLong(&mask))
        mask = 0;
    options = 0;
    if(CheckBox1->IsChecked())
        options += 1;

    indication_type =  Choice4->GetSelection();
    dataref_type = Choice3->GetSelection();
    wxString tmpwxstr = TextCtrl12->GetValue();
    const char *data = tmpwxstr.c_str().AsChar();
    int data_len = strlen(data);
    data_len = min_(length,data_len);

    switch(indication_type)
    {
    case 1: /*NUMERIC*/
        if(device >=0 && device < devs && position >=0 && position <8 && data_len > 0 && data_len <= 8)
            memcpy(&display_array[4+8*device + position],data,data_len);
        break;

    case 2: /*DISCRETE*/
        int value = atoi(data);
        if(position >=0 && position < discrete_tape_len)
            led_array[position+4] = '0' + (value & 1);
        break;
    }


#if 1
    //ComboBox3->GetValue().ToLong(&val);

    switch(++state)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 9:

    case 2:
    case 4:
    case 6:
    case 8:



        if(current_panel == 2 || current_panel == 3)
            ;
        else
            break;

        display_array[0] = '{';
        display_array[1] = '7';
        display_array[2] = 'S';
        display_array[3] = 'G';
        display_array[numeric_tape_len + 4] = '}';
        display_array[numeric_tape_len + 5] = 0;

        res = serial_port.SerialWrite((unsigned char*)display_array, numeric_tape_len + 5);

        if(current_panel == 2 || current_panel == 4)
            ;
        else
            break;

        led_array[0] = '{';
        led_array[1] = 'L';
        led_array[2] = 'E';
        led_array[3] = 'D';
        led_array[discrete_tape_len + 4] = '}';
        led_array[discrete_tape_len + 5] = 0;


        res = serial_port.SerialWrite((unsigned char*)led_array, discrete_tape_len + 5);

        break;
    case 10:
#ifdef PARANOIC_TEST
        printf("D");
#endif
        //if(current_panel != 0)
        //    break;
        res = serial_port.SerialWrite((unsigned char*)"{DET}", 5);
        if(!CheckBox2->IsChecked())
        {
            set_text_color(BRIGHT_CYAN);
            printf("{DET}\n");
            set_text_color(BRIGHT_WHITE);
        }
        state = 0;
    }


#endif
    if(res == -1)
    {
        connection_flag = 0;
        StaticText2->SetForegroundColour(clRed);
        StaticText2->SetLabel("Comm.Error");

    }
    else if(++connection_timer == 20)
    {
        connection_flag = 0;
        StaticText2->SetForegroundColour(clDarkYellow);
        StaticText2->SetLabel("Disconnected");
    }
#ifdef PARANOIC_TEST
    printf("t");
#endif
}





void loggerDialog::OnClose(wxCloseEvent& event)
{

}

void loggerDialog::OnCheckBox1Click(wxCommandEvent& event)
{
}

void loggerDialog::OnChoice1Select1(wxCommandEvent& event)
{
    controls_params_selector();
}


void loggerDialog::OnChoice2Select(wxCommandEvent& event)
{
    controls_params_selector();
}



int loggerDialog::controls_params_selector(void)
{
    int data_type = Choice1->GetSelection();
    int control_type = Choice2->GetSelection();
    const int selection_table[6][6] =
    {
        /*                    NONE CMD   DREF_FL  DREF_INT  ARRAY_FL  ARRAY_INT */
        /*NONE           */ { 0,   0,    0,     0,      0,      0    },
        /*BUTTON         */ { 0,   0x80, 0x83,  0x83,   0xA3,   0xA3 },
        /*CYCLIC_BUTTON  */ { 0,   0x00, 0x9C,  0x9C,   0xBC,   0xBC },
        /*TOGGLE_SWITCH  */ { 0,   0xC0, 0x83,  0x83,   0xA3,   0xA3 },
        /*ROTARY_SW_POS  */ { 0,   0x80, 0x82,  0x82,   0xA2,   0xA2 },
        /*ENCODER        */ { 0,   0x80, 0x9C,  0x9C,   0xBC,   0xBC },
    };

    int mask = 0xff & selection_table[control_type][data_type];

    if(mask & 1)
        TextCtrl9->Enable();
    else
        TextCtrl9->Disable();
    if(mask & 2)
        TextCtrl8->Enable();
    else
        TextCtrl8->Disable();
    if(mask & 4)
        TextCtrl3->Enable();
    else
        TextCtrl3->Disable();
    if(mask & 8)
        TextCtrl4->Enable();
    else
        TextCtrl4->Disable();
    if(mask & 16)
        TextCtrl5->Enable();
    else
        TextCtrl5->Disable();
    if(mask & 32)
        TextCtrl6->Enable();
    else
        TextCtrl6->Disable();
    if(mask & 64)
        TextCtrl17->Enable();
    else
        TextCtrl17->Disable();
    if(mask & 128)
        TextCtrl1->Enable();
    else
        TextCtrl1->Disable();


    return selection_table[control_type][data_type];
}

int loggerDialog::indication_params_selector(void)
{
    int data_type = Choice3->GetSelection();
    int indication_type = Choice4->GetSelection();
    const int selection_table[3] =
    {
        /*                  NONE  DISCR  NUMB  */
        /*NONE           */  0,   0x5F,  0x22
    };
    int mask = 0xff & selection_table[indication_type];

    if(data_type == IND_ARRAY_INT || data_type == IND_ARRAY_FLOAT)
        mask |= 0x80;

    if(mask & 1)
        TextCtrl14->Enable();
    else
        TextCtrl14->Disable();
    if(mask & 2)
        TextCtrl15->Enable();
    else
        TextCtrl15->Disable();
    if(mask & 4)
        TextCtrl16->Enable();
    else
        TextCtrl16->Disable();
    if(mask & 8)
        TextCtrl18->Enable();
    else
        TextCtrl18->Disable();
    if(mask & 16)
        TextCtrl19->Enable();
    else
        TextCtrl19->Disable();
    if(mask & 32)
        TextCtrl20->Enable();
    else
        TextCtrl20->Disable();
    if(mask & 64)
        CheckBox1->Enable();
    else
        CheckBox1->Disable();

    if(mask & 128)
        TextCtrl21->Enable();
    else
        TextCtrl21->Disable();

    return mask;


}

void loggerDialog::OnButton5Click(wxCommandEvent& event)
{
    wxString str = "",
             wxstr_command_0,
             wxstr_command_1,
             wxstr_command,
             wxstr_dataref;
    long val, index, min_value, max_value, increment, _0,_1;
    const char *dataref = (wxstr_dataref = TextCtrl1->GetValue()).c_str().AsChar();
    const char *command = (wxstr_command = TextCtrl1->GetValue()).c_str().AsChar();
    const char *command_0 = (wxstr_command_0 = TextCtrl1->GetValue()).c_str().AsChar();
    const char *command_1 = (wxstr_command_1 = TextCtrl17->GetValue()).c_str().AsChar();

    int data_type = Choice1->GetSelection();
    int control_type = Choice2->GetSelection();

    controls_params_selector();
    if(!TextCtrl10->GetValue().ToLong(&val))
        val = 0;
    if(!TextCtrl6->GetValue().ToLong(&index))
        index = 0;

    if(!TextCtrl9->GetValue().ToLong(&_0))
        _0 = 0;
    if(!TextCtrl8->GetValue().ToLong(&_1))
        _1 = 0;

    if(!TextCtrl3->GetValue().ToLong(&min_value))
        min_value = 0;
    if(!TextCtrl4->GetValue().ToLong(&max_value))
        max_value = 0;
    if(!TextCtrl5->GetValue().ToLong(&increment))
        increment = 0;


    switch(control_type)
    {
////////////////////////////////////////////////////////////
/////////////////////////// BUTTON /////////////////////////
////////////////////////////////////////////////////////////
    case BUTTON:
        switch(data_type)
        {
        case COMMAND:

            str.Printf("\
[Key%04d]\r\n\
mode: command\r\n\
command: %s\r\n\r\n",
                       val,
                       command);
            break;

        case DATAREF_INT:
            str.Printf("\
[Key%04d]\r\n\
mode: dataref\r\n\
dataref: %s\r\n\
type: int\r\n\
0: %d\r\n\
1: %d\r\n\r\n",
                       val,
                       dataref,
                       _0,
                       _1
                      );

            break;

        case DATAREF_FLOAT:

            str.Printf("\
[Key%04d]\r\n\
mode: dataref\r\n\
dataref: %s\r\n\
type: float\r\n\
0: %d\r\n\
1: %d\r\n\r\n",
                       val,
                       dataref,
                       _0,
                       _1
                      );
            break;

        case ARRAY_INT:

            str.Printf("\
[Key%04d]\r\n\
mode: dataref\r\n\
array: %s\r\n\
index: %d\r\n\
type: int\r\n\
0: %d\r\n\
1: %d\r\n\r\n",
                       val,
                       dataref,
                       index,
                       _0,
                       _1
                      );
            break;

        case ARRAY_FLOAT:
            str.Printf("\
[Key%04d]\r\n\
mode: dataref\r\n\
array: %s\r\n\
index: %d\r\n\
type: float\r\n\
0: %d\r\n\
1: %d\r\n\r\n",
                       val,
                       dataref,
                       index,
                       _0,
                       _1
                      );
            break;
        }



        break;

////////////////////////////////////////////////////////////////////
//////////////////////////// CYCLIC BUTTON /////////////////////////
////////////////////////////////////////////////////////////////////

    case CYCLIC_BUTTON:
        switch(data_type)
        {
        case COMMAND:
            // not applicable
            break;
        case DATAREF_INT:
            str.Printf("\
[Key%04d]\r\n\
mode: loop\r\n\
dataref: %s\r\n\
type: int\r\n\
min: %d\r\n\
max: %d\r\n\
increment: %d\r\n\r\n",
                       val,
                       dataref,
                       min_value,
                       max_value,
                       increment
                      );
            break;

        case DATAREF_FLOAT:
            str.Printf("\
[Key%04d]\r\n\
mode: loop\r\n\
dataref: %s\r\n\
type: float\r\n\
min: %d\r\n\
max: %d\r\n\
increment: %d\r\n\r\n",
                       val,
                       dataref,
                       min_value,
                       max_value,
                       increment
                      );
            break;

        case ARRAY_INT:
            str.Printf("\
[Key%04d]\r\n\
mode: loop\r\n\
array: %s\r\n\
index: %d\r\n\
type: int\r\n\
min: %d\r\n\
max: %d\r\n\
increment: %d\r\n\r\n",
                       val,
                       dataref,
                       index,
                       min_value,
                       max_value,
                       increment
                      );
            break;

        case ARRAY_FLOAT:
            str.Printf("\
[Key%04d]\r\n\
mode: loop\r\n\
array: %s\r\n\
index: %d\r\n\
type: float\r\n\
min: %d\r\n\
max: %d\r\n\
increment: %d\r\n\r\n",
                       val,
                       dataref,
                       index,
                       min_value,
                       max_value,
                       increment
                      );
            break;
        }

        break;

////////////////////////////////////////////////////////////////////
//////////////////////////// TOGGLE SWITCH /////////////////////////
////////////////////////////////////////////////////////////////////

    case TOGGLE_SWITCH:

        switch(data_type)
        {
        case COMMAND:
            str.Printf("\
[Key%04d]\r\n\
mode: command-toggle\r\n\
command_0: %s\r\n\
command_1: %s\r\n\r\n",
                       val,
                       command_0,
                       command_1
                      );
            printf("command_1: %s\n", command_1);
            break;
        case DATAREF_INT:
            str.Printf("\
[Key%04d]\r\n\
mode: dataref\r\n\
dataref: %s\r\n\
type: int\r\n\
0: %d\r\n\
1: %d\r\n\r\n",
                       val,
                       dataref,
                       _0,
                       _1
                      );
            break;

        case DATAREF_FLOAT:
            str.Printf("\
[Key%04d]\r\n\
mode: dataref\r\n\
dataref: %s\r\n\
type: float\r\n\
0: %d\r\n\
1: %d\r\n\r\n",
                       val,
                       dataref,
                       _0,
                       _1
                      );
            break;

        case ARRAY_INT:
            str.Printf("\
[Key%04d]\r\n\
mode: dataref\r\n\
array: %s\r\n\
index: %d\r\n\
type: int\r\n\
0: %d\r\n\
1: %d\r\n\r\n",
                       val,
                       dataref,
                       index,
                       _0,
                       _1
                      );
            break;

        case ARRAY_FLOAT:
            str.Printf("\
[Key%04d]\r\n\
mode: dataref\r\n\
array: %s\r\n\
index: %d\r\n\
type: float\r\n\
0: %d\r\n\
1: %d\r\n\r\n",
                       val,
                       dataref,
                       index,
                       _0,
                       _1
                      );
            break;
        }


        break;

/////////////////////////////////////////////////////////////////////////////
//////////////////////////// ROTARY SWITCH POSITION /////////////////////////
/////////////////////////////////////////////////////////////////////////////

    case ROTARY_SWITCH_POSITION:
        switch(data_type)
        {
        case COMMAND:
            str.Printf("\
[Key%04d]\r\n\
mode: command\r\n\
command: %s\r\n\r\n",
                       val,
                       command);
            break;
        case DATAREF_INT:
            str.Printf("\
[Key%04d]\r\n\
mode: dataref\r\n\
dataref: %s\r\n\
type: int\r\n\
1: %d\r\n\r\n",
                       val,
                       dataref,
                       _1
                      );
            break;

        case DATAREF_FLOAT:
            str.Printf("\
[Key%04d]\r\n\
mode: dataref\r\n\
dataref: %s\r\n\
type: float\r\n\
1: %d\r\n\r\n",
                       val,
                       dataref,
                       _1
                      );

            break;

        case ARRAY_INT:
            str.Printf("\
[Key%04d]\r\n\
mode: dataref\r\n\
array: %s\r\n\
index: %d\r\n\
type: int\r\n\
1: %d\r\n\r\n",
                       val,
                       dataref,
                       index,
                       _1
                      );

            break;

        case ARRAY_FLOAT:
            str.Printf("\
[Key%04d]\r\n\
mode: dataref\r\n\
array: %s\r\n\
index: %d\r\n\
type: float\r\n\
1: %d\r\n\r\n",
                       val,
                       dataref,
                       index,
                       _1
                      );

            break;
        }
        break;

//////////////////////////////////////////////////////////////
//////////////////////////// ENCODER /////////////////////////
//////////////////////////////////////////////////////////////
    case ENCODER:
        switch(data_type)
        {
        case COMMAND:
            str.Printf("\
[Key%04d]\r\n\
mode: command\r\n\
command: %s\r\n\r\n",
                       val,
                       command);
            break;

        case DATAREF_INT:
            str.Printf("\
[Key%04d]\r\n\
mode: dataref\r\n\
dataref: %s\r\n\
type: int\r\n\
min: %d\r\n\
max: %d\r\n\
increment: %d\r\n\r\n",
                       val,
                       dataref,
                       min_value,
                       max_value,
                       increment
                      );
            break;

        case DATAREF_FLOAT:
            str.Printf("\
[Key%04d]\r\n\
mode: dataref\r\n\
dataref: %s\r\n\
type: float\r\n\
min: %d\r\n\
max: %d\r\n\
increment: %d\r\n\r\n",
                       val,
                       dataref,
                       min_value,
                       max_value,
                       increment
                      );
            break;

        case ARRAY_INT:
            str.Printf("\
[Key%04d]\r\n\
mode: dataref\r\n\
array: %s\r\n\
index: %d\r\n\
type: int\r\n\
min: %d\r\n\
max: %d\r\n\
increment: %d\r\n\r\n",
                       val,
                       dataref,
                       index,
                       min_value,
                       max_value,
                       increment
                      );
            break;

        case ARRAY_FLOAT:
            str.Printf("\
[Key%04d]\r\n\
mode: dataref\r\n\
array: %s\r\n\
index: %d\r\n\
type: float\r\n\
min: %d\r\n\
max: %d\r\n\
increment: %d\r\n\r\n",
                       val,
                       dataref,
                       index,
                       min_value,
                       max_value,
                       increment
                      );
            break;
        }
        break;
    }

    if(str.Len())
    {
        int rem_max_len = GetMaxLen(TextCtrl2);
        wxString tmp;
        if(rem_max_len)
        {
            AddHashLine(TextCtrl7, '#', rem_max_len+3);
            int i;
            for(i=0; i < TextCtrl2->GetNumberOfLines(); i++)
            {
                tmp = "# " + TextCtrl2->GetLineText(i) + "\r\n";
                TextCtrl7->AppendText(tmp);
            }
            AddHashLine(TextCtrl7, '#', rem_max_len+3);

        }
        TextCtrl7->AppendText(str);
    }


}

void loggerDialog::AddHashLine(wxTextCtrl *ed, int symbol, int number)
{
    int i;
    wxString str = "",s;
    s.Printf("%c",symbol);

    for(i = 0; i < number; i++)
        str += s;
    str += "\r\n";
    ed->AppendText(str);
}


void loggerDialog::OnChoice3Select(wxCommandEvent& event)
{
    indication_params_selector();
}

void loggerDialog::OnChoice4Select(wxCommandEvent& event)
{
    indication_params_selector();
}

void loggerDialog::OnButton6Click(wxCommandEvent& event)
{
    const char *data_type_name[2] = {"int", "float"};
    wxString str;
    long index, device, position, length, factor,offset,mask,options = 0;
    int data_type = Choice3->GetSelection();
    int indication_type = Choice4->GetSelection();

    int index_present =  1 && TextCtrl21->GetValue().Len(),
        device_present = 1 && TextCtrl14->GetValue().Len(),
        position_present = 1 && TextCtrl15->GetValue().Len(),
        length_present = 1 && TextCtrl16->GetValue().Len(),
        factor_present = 1 && TextCtrl18->GetValue().Len(),
        offset_present = 1 && TextCtrl19->GetValue().Len(),
        mask_present = 1 && TextCtrl20->GetValue().Len();




    if(!TextCtrl21->GetValue().ToLong(&index))
        index = 0;
    if(!TextCtrl14->GetValue().ToLong(&device))
        device = 0;

    if(!TextCtrl15->GetValue().ToLong(&position))
        position = 0;
    if(!TextCtrl16->GetValue().ToLong(&length))
        length = 0;

    if(!TextCtrl18->GetValue().ToLong(&factor))
        factor = 0;
    if(!TextCtrl19->GetValue().ToLong(&offset))
        offset = 0;
    if(!TextCtrl20->GetValue().ToLong(&mask))
        mask = 0;

    if(CheckBox1->IsChecked())
        options |= 1;

    if((indication_type == NUMERIC || indication_type == DISCRETE) &&
            data_type > 0
      )
    {
        int rem_max_len = GetMaxLen(TextCtrl2);
        wxString tmp;
        if(rem_max_len)
        {
            AddHashLine(TextCtrl7, '#', rem_max_len+3);
            int i;
            for(i=0; i < TextCtrl2->GetNumberOfLines(); i++)
            {
                tmp = "# " + TextCtrl2->GetLineText(i) + "\r\n";
                TextCtrl7->AppendText(tmp);
            }
            AddHashLine(TextCtrl7, '#', rem_max_len+3);

        }
    }



    switch(indication_type)
    {
    case NUMERIC:


        if((data_type - 1) & 2)
        {
            str.Printf("\
[IND %s]\r\n\
mode: datarefPoll\r\n\
array: %s\r\n\
index: %d\r\n\
type: %s\r\n\
devadr: %d\r\n\
pos: %d\r\n\
len: %d\r\n\
",
                       TextCtrl13->GetValue().c_str().AsChar(),
                       TextCtrl11->GetValue().c_str().AsChar(),
                       index,
                       data_type_name[(data_type - 1) & 1],
                       device,
                       position,
                       length
                      );


        }
        else
        {
            str.Printf("\
[IND %s]\r\n\
mode: datarefPoll\r\n\
dataref: %s\r\n\
type: %s\r\n\
devadr: %d\r\n\
pos: %d\r\n\
len: %d\r\n\
",
                       TextCtrl13->GetValue().c_str().AsChar(),
                       TextCtrl11->GetValue().c_str().AsChar(),
                       data_type_name[(data_type - 1) & 1],
                       device,
                       position,
                       length
                      );


        }


        TextCtrl7->AppendText(str);



        if(factor_present)
        {
            str.Printf("factor: %d\r\n",factor);
            TextCtrl7->AppendText(str);
        }

        if(offset_present)
        {
            str.Printf("offset: %d\r\n",offset);
            TextCtrl7->AppendText(str);
        }

        if(options)
        {
            str.Printf("options: %d\r\n",options);
            TextCtrl7->AppendText(str);
        }
        TextCtrl7->AppendText("\r\n");
        break;

    case DISCRETE:

        if((data_type - 1) & 2)
        {
            str.Printf("\
[IND %s]\r\n\
mode: datarefPoll\r\n\
array: %s\r\n\
index: %d\r\n\
type: %s\r\n\
pos: %d\r\n\
",
                       TextCtrl13->GetValue().c_str().AsChar(),
                       TextCtrl11->GetValue().c_str().AsChar(),
                       index,
                       data_type_name[(data_type - 1) & 1],
                       position
                      );
        }
        else
        {
            str.Printf("\
[IND %s]\r\n\
mode: datarefPoll\r\n\
dataref: %s\r\n\
type: %s\r\n\
pos: %d\r\n\
",
                       TextCtrl13->GetValue().c_str().AsChar(),
                       TextCtrl11->GetValue().c_str().AsChar(),
                       data_type_name[(data_type - 1) & 1],
                       position
                      );

        }

        TextCtrl7->AppendText(str);

        if(mask_present)
        {
            str.Printf("mask: %d\r\n",mask);
            TextCtrl7->AppendText(str);
        }
        TextCtrl7->AppendText("\r\n");

        break;


    }

}



void loggerDialog::OnButton7Click(wxCommandEvent& event)
{
    memset(display_array+4,' ',128);
    memset(led_array+4,'0',64);


}

void loggerDialog::OnComboBox1Selected(wxCommandEvent& event)
{


}

void loggerDialog::OnButton8Click(wxCommandEvent& event)
{
    StaticText2->SetForegroundColour(clDarkYellow);
    connection_flag = 0;
    connection_timer = 0;
    StaticText2->SetLabel("Disconnected");
    timer_enabled = 50;
    serial_port.DTR_off();
    Timer2.Start(500);
}

void loggerDialog::OnTimer2Trigger(wxTimerEvent& event)
{
    serial_port.DTR_on();
    Timer2.Stop();
}



void loggerDialog::OnButton9Click1(wxCommandEvent& event)
{
    console_flag ^= 1;

    if(console_flag&1)
    {
        AllocConsole();
        //freopen("conin$",  "r", stdin); //console input buffer
        freopen("conout$", "w", stdout);//console output buffer
        freopen("conout$", "w", stderr); //console error device
        console_init("Debug console");
        CheckBox2->Enable(true);
    }
    else
    {
        fclose(stderr);
        fclose(stdout);
        console_close();
        FreeConsole();
        CheckBox2->Enable(false);

    }
}



void loggerDialog::OnCheckBox2Click(wxCommandEvent& event)
{
}

void loggerDialog::OnNotebook1PageChanged(wxNotebookEvent& event)
{
   current_panel = Notebook1->GetSelection();

   //  int sel = Choice6->GetSelection();
   // switch(sel)
   // {
   // case 0:
   //     break;
   // case 1:
   // case 2:
   //     TextCtrl48->Enable(false);
   //     break;
   // case 3:
   // case 4:
   //     TextCtrl48->Enable(true);
   //     break;
   // }

}

void loggerDialog::OnChoice5Select(wxCommandEvent& event)
{
    wxColor fgcl,bgcl;
    wxFont fnt0,fnt1;
    fgcl = TextCtrl42->GetForegroundColour();
    bgcl = TextCtrl42->GetBackgroundColour();
    fnt0 == TextCtrl42->GetFont();
    fnt1 = fnt0;
    fnt1.MakeBold();
    int sel = Choice5->GetSelection();
    int i;
    for(i=0; i<16; i++)
    {
        if(sel == i)
        {
            axes[i]->SetForegroundColour(wxColor(255,255,255));
            axes[i]->SetBackgroundColour(wxColor(0,0,0));
            axes[i]->SetFont(fnt1);
        }
        else
        {
            axes[i]->SetForegroundColour(fgcl);
            axes[i]->SetBackgroundColour(bgcl);
            axes[i]->SetFont(fnt0);
        }
        axes[i]->Refresh();
    }


}

void loggerDialog::OnButton12Click(wxCommandEvent& event)
{
    int sel = Choice5->GetSelection();
    TextCtrl44->SetValue(axes[sel]->GetValue());
}

void loggerDialog::OnButton13Click(wxCommandEvent& event)
{
    int sel = Choice5->GetSelection();
    TextCtrl52->SetValue(axes[sel]->GetValue());
}

void loggerDialog::OnButton14Click(wxCommandEvent& event)
{
    int sel = Choice5->GetSelection();
    TextCtrl53->SetValue(axes[sel]->GetValue());
}

void loggerDialog::OnCheckBox3Click(wxCommandEvent& event)
{
    TextCtrl52->Enable(CheckBox3->IsChecked());
    Button13->Enable(CheckBox3->IsChecked());
}

void loggerDialog::OnChoice6Select(wxCommandEvent& event)
{
    int sel = Choice6->GetSelection();
    switch(sel)
    {
    case 0:
        break;
    case 1:
    case 2:
        TextCtrl48->Enable(false);
        break;
    case 3:
    case 4:
        TextCtrl48->Enable(true);
        break;
    }
}

void loggerDialog::OnButton10Click2(wxCommandEvent& event)
{
    const char *data_type_name[5] = {"", "int", "float", "int", "float"};
    wxString str;
    long index, devmax, devcenter, devmin;
    double simmax,simmin;
    int data_type = Choice6->GetSelection();
    int has_center = 1 && CheckBox3->IsChecked();
    int axis_ndx = Choice5->GetSelection();
    double factor = 1;
    double offset = 0;
    int index_present =  1 && TextCtrl48->GetValue().Len(),
        devmax_present = 1 && TextCtrl44->GetValue().Len(),
        devcenter_present = 1 && TextCtrl52->GetValue().Len(),
        devmin_present = 1 && TextCtrl53->GetValue().Len(),
        simmin_present = 1 && TextCtrl54->GetValue().Len(),
        simmax_present = 1 && TextCtrl55->GetValue().Len();

    if(!TextCtrl48->GetValue().ToLong(&index))
        index = 0;

    if(!TextCtrl44->GetValue().ToLong(&devmax))
        devmax = 0;

    if(!TextCtrl52->GetValue().ToLong(&devcenter))
        devcenter = 0;

    if(!TextCtrl53->GetValue().ToLong(&devmin))
        devmin = 0;

    if(!TextCtrl54->GetValue().ToDouble(&simmax))
        simmax = 0;

    if(!TextCtrl55->GetValue().ToDouble(&simmin))
        simmin = 0;


        if(CheckBox3->IsChecked())
        {
           factor = (simmax - simmin) / (devmax - devmin);
           offset = 1.0 * devcenter;
        }
        else
        {
           factor = (simmax - simmin) / (1.0*(devmax - devmin));
           offset = 1.0 * devmax - simmax/factor;
        }


        int rem_max_len = GetMaxLen(TextCtrl2);
        wxString tmp;
        if(rem_max_len)
        {
            AddHashLine(TextCtrl7, '#', rem_max_len+3);
            int i;
            for(i=0; i < TextCtrl2->GetNumberOfLines(); i++)
            {
                tmp = "# " + TextCtrl2->GetLineText(i) + "\r\n";
                TextCtrl7->AppendText(tmp);
            }
            AddHashLine(TextCtrl7, '#', rem_max_len+3);

        }

    switch(data_type)
    {
    case 0:
        break;
    case 1:
    case 2:
            str.Printf("\
[Axis %s]\r\n\
mode: input\r\n\
dataref: %s\r\n\
type: %s\r\n\
axis: %d\r\n\
factor: %11.5f\r\n\
offset: %6.0f\r\n\r\n\
",
                       TextCtrl43->GetValue().c_str().AsChar(),
                       TextCtrl42->GetValue().c_str().AsChar(),
                       data_type_name[data_type],
                       axis_ndx,
                       factor,
                       offset
                      );
        break;

    case 3:
    case 4:
            str.Printf("\
[Axis %s]\r\n\
mode: input\r\n\
array: %s\r\n\
index: %s\r\n\
type: %s\r\n\
axis: %d\r\n\
factor: %11.5f\r\n\
offset: %6.0f\r\n\r\n\
",
                       TextCtrl43->GetValue().c_str().AsChar(),
                       TextCtrl42->GetValue().c_str().AsChar(),
                       index,
                       data_type_name[data_type],
                       axis_ndx,
                       factor,
                       offset
                      );

        break;
    }
    TextCtrl7->AppendText(str);

}



/*
https://www.onlinegdb.com/

#####################
# Whitout center
#####################
simmin = 40
simmax = 240
devmin = 1023
devmax = 200

factor = (simmax-simmin) / (devmax - devmin)
offset = devmax - simmax/factor


print("factor=",factor)
print("offset=",offset)
print("sim(devmax)=",(devmax-offset)*factor)
print("sim(devmin)=",(devmin-offset)*factor)


*/

void loggerDialog::OnButton15Click(wxCommandEvent& event)
{
  TextCtrl12->SetValue(TextCtrl23->GetValue());
}

void loggerDialog::OnButton16Click(wxCommandEvent& event)
{
  TextCtrl12->SetValue(TextCtrl24->GetValue());
}

void loggerDialog::OnButton17Click(wxCommandEvent& event)
{
  TextCtrl12->SetValue(TextCtrl45->GetValue());
}

void loggerDialog::OnButton18Click(wxCommandEvent& event)
{
    TextCtrl50->SetValue(TextCtrl62->GetValue());
}

void loggerDialog::OnButton19Click(wxCommandEvent& event)
{
    TextCtrl56->SetValue(TextCtrl62->GetValue());
}

void loggerDialog::OnButton20Click(wxCommandEvent& event)
{
    TextCtrl58->SetValue(TextCtrl62->GetValue());
}

void loggerDialog::OnButton21Click(wxCommandEvent& event)
{
   const char *data_type_name[5] = {"", "int", "float", "int", "float"};
    wxString str;
    long index, devmax, devcenter, devmin;
    double simmax,simmin;
    int data_type = Choice7->GetSelection();
    int has_center = 1 && CheckBox4->IsChecked();
    double factor = 1;
    double offset = 0;
    int index_present =  1 && TextCtrl49->GetValue().Len(),
        devmax_present = 1 && TextCtrl50->GetValue().Len(),
        devcenter_present = 1 && TextCtrl56->GetValue().Len(),
        devmin_present = 1 && TextCtrl58->GetValue().Len(),
        simmin_present = 1 && TextCtrl57->GetValue().Len(),
        simmax_present = 1 && TextCtrl51->GetValue().Len();

    if(!TextCtrl49->GetValue().ToLong(&index))
        index = 0;

    if(!TextCtrl50->GetValue().ToLong(&devmax))
        devmax = 0;

    if(!TextCtrl56->GetValue().ToLong(&devcenter))
        devcenter = 0;

    if(!TextCtrl58->GetValue().ToLong(&devmin))
        devmin = 0;

    if(!TextCtrl51->GetValue().ToDouble(&simmax))
        simmax = 0;

    if(!TextCtrl57->GetValue().ToDouble(&simmin))
        simmin = 0;


       if(devmax_present &&
         devcenter_present &&
         devmin_present &&
         simmin_present &&
         simmax_present )
       {
        if(CheckBox4->IsChecked())
        {
           factor = (simmax - simmin) / (devmax - devmin);
           offset = 1.0 * devcenter;
        }
        else
        {
           factor = (simmax - simmin) / (1.0*(devmax - devmin));
           offset = 1.0 * devmax - simmax/factor;
        }
       }
       else
       {
           factor = 1;
           offset = 0;
       }

        int rem_max_len = GetMaxLen(TextCtrl2);
        wxString tmp;
        if(rem_max_len)
        {
            AddHashLine(TextCtrl7, '#', rem_max_len+3);
            int i;
            for(i=0; i < TextCtrl2->GetNumberOfLines(); i++)
            {
                tmp = "# " + TextCtrl2->GetLineText(i) + "\r\n";
                TextCtrl7->AppendText(tmp);
            }
            AddHashLine(TextCtrl7, '#', rem_max_len+3);

        }

    switch(data_type)
    {
    case 0:
        break;
    case 1:
    case 2:
            str.Printf("\
[Inp%s]\r\n\
mode: input\r\n\
dataref: %s\r\n\
type: %s\r\n\
factor: %11.5f\r\n\
offset: %6.0f\r\n\r\n\
",
                       TextCtrl60->GetValue().c_str().AsChar(),
                       TextCtrl46->GetValue().c_str().AsChar(),
                       data_type_name[data_type],
                       factor,
                       offset
                      );
        break;

    case 3:
    case 4:
            str.Printf("\
[Inp%s]\r\n\
mode: input\r\n\
array: %s\r\n\
index: %s\r\n\
type: %s\r\n\
factor: %11.5f\r\n\
offset: %6.0f\r\n\r\n\
",
                       TextCtrl60->GetValue().c_str().AsChar(),
                       TextCtrl46->GetValue().c_str().AsChar(),
                       index,
                       data_type_name[data_type],
                       factor,
                       offset
                      );

        break;
    }
    TextCtrl7->AppendText(str);


}

void loggerDialog::OnCheckBox4Click(wxCommandEvent& event)
{
    TextCtrl56->Enable(CheckBox4->IsChecked());
    Button19->Enable(CheckBox4->IsChecked());
}

void loggerDialog::OnChoice7Select(wxCommandEvent& event)
{
    int sel = Choice7->GetSelection();
    switch(sel)
    {
    case 0:
        break;
    case 1:
    case 2:
        TextCtrl49->Enable(false);
        break;
    case 3:
    case 4:
        TextCtrl49->Enable(true);
        break;
    }

}

void loggerDialog::OnPanel6MouseEnter(wxMouseEvent& event)
{

}

void loggerDialog::OnPanel6Paint(wxPaintEvent& event)
{
    int sel = Choice7->GetSelection();
    switch(sel)
    {
    case 0:
        break;
    case 1:
    case 2:
        TextCtrl49->Enable(false);
        break;
    case 3:
    case 4:
        TextCtrl49->Enable(true);
        break;
    }
}

void loggerDialog::OnButton22Click(wxCommandEvent& event)
{
    long port;
    TextCtrl47->GetValue().ToLong(&port);
    if(0 == udp_server.Open(port))
    {
        Button22->Enable(false);
        TextCtrl47->Enable(false);
        Button23->Enable(true);
    }
}

void loggerDialog::OnButton23Click(wxCommandEvent& event)
{
     udp_server.Close();
     Button22->Enable(true);
     TextCtrl47->Enable(true);
     Button23->Enable(false);
}

void loggerDialog::OnComboBox4Selected(wxCommandEvent& event)
{
    memset(display_array,' ',sizeof(display_array));
    memset(led_array,'0',sizeof(led_array));
}

void loggerDialog::OnButton24Click(wxCommandEvent& event)
{
   memset(display_array,' ',sizeof(display_array));
   memset(led_array,'0',sizeof(led_array));
}

void loggerDialog::OnComboBox3Selected(wxCommandEvent& event)
{
    memset(display_array,' ',sizeof(display_array));
    memset(led_array,'0',sizeof(led_array));
}
