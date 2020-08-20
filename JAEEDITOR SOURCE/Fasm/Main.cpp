#include <Windows.h>
HINSTANCE hRTFLib = LoadLibrary("RICHED32.DLL");
HINSTANCE hIns = LoadLibrary("SciLexer.DLL"); 
#include <D:\\Desktop\\Fasm\\Fasm\\scintilla\\include\\SciLexer.h>
#include <D:\\Desktop\\Fasm\\Fasm\scintilla\\include\\Scintilla.h>
#include <D:\\Desktop\\Fasm\\Fasm\scintilla\\include\\ScintillaWidget.h>
#include "winuser.h"
#include <Commctrl.h>
#include <string>
#include "resource.h"
#include "Windowsx.h"
#include <Richedit.h>
#include <Psapi.h>
#include <fcntl.h>
#include <vector>
#include <algorithm>

#include "WndClass.h"
#include "General.h"

using namespace std;
 
#pragma comment (lib ,"Comctl32.lib")

#define MYWM_NOTIFYICON (WM_USER + 1)
#define ID_KEY_O		 (1879)
#define ID_KEY_P		 (2879)
#define ID_KEY_S		 (3879)
#define ID_KEY_N		 (4879)
#define ID_KEY_SHIFT_S   (5879)
#define ID_KEY_F		 (6879)
#define ID_KEY_SHIFT_F   (7879)
#define ID_KEY_SHIFT_TAB (8879)
#define ID_KEY_SHIFT_Q   (9879)
#define ID_KEY_SHIFT_C   (9579)
#define ID_KEY_SHIFT_X   (9679)

HINSTANCE hInst = GetModuleHandle(NULL);
HGLOBAL hResource = LoadResource(hInst, FindResource(hInst,MAKEINTRESOURCE(IDR_TXT1),"TXT"));
		char* HelloWorld = (char*)LockResource(hResource);
HGLOBAL hResource3 = LoadResource(hInst, FindResource(hInst,MAKEINTRESOURCE(IDR_TXT2),"TXT"));
		char* HelloWorld2 = (char*)LockResource(hResource3);
HGLOBAL hResource4 = LoadResource(hInst, FindResource(hInst,MAKEINTRESOURCE(IDR_TXT3),"TXT"));
		char* HelloWorld3 = (char*)LockResource(hResource4);
HGLOBAL hResource5 = LoadResource(hInst, FindResource(hInst,MAKEINTRESOURCE(IDR_TXT4),"TXT"));
		char* HelloWorld4 = (char*)LockResource(hResource5);
HGLOBAL hResource6 = LoadResource(hInst, FindResource(hInst,MAKEINTRESOURCE(IDR_TXT5),"TXT"));
		char* HelloWorld5 = (char*)LockResource(hResource6);
HGLOBAL hResourceDLL = LoadResource(hInst, FindResource(hInst,MAKEINTRESOURCE(IDR_TXT6),"TXT"));
		char* DLL = (char*)LockResource(hResourceDLL);
HGLOBAL hResourceDLL2 = LoadResource(hInst, FindResource(hInst,MAKEINTRESOURCE(IDR_TXT7),"TXT"));
		char* DLL2 = (char*)LockResource(hResourceDLL2);
HGLOBAL hResourceMINIPAD = LoadResource(hInst, FindResource(hInst,MAKEINTRESOURCE(IDR_TXT8),"TXT"));
		char* MINIPAD = (char*)LockResource(hResourceMINIPAD);
HGLOBAL hResourceMSCOFF = LoadResource(hInst, FindResource(hInst,MAKEINTRESOURCE(IDR_TXT9),"TXT"));
		char* MSCOFF = (char*)LockResource(hResourceMSCOFF);
HGLOBAL hResourceOPENGL = LoadResource(hInst, FindResource(hInst,MAKEINTRESOURCE(IDR_TXT10),"TXT"));
		char* OPENGL = (char*)LockResource(hResourceOPENGL);
HGLOBAL hResourcePEDEMO = LoadResource(hInst, FindResource(hInst,MAKEINTRESOURCE(IDR_TXT11),"TXT"));
		char* PEDEMO = (char*)LockResource(hResourcePEDEMO);
HGLOBAL hResourceTEMPLATE = LoadResource(hInst, FindResource(hInst,MAKEINTRESOURCE(IDR_TXT12),"TXT"));
		char* TEMPLATE = (char*)LockResource(hResourceTEMPLATE);
HGLOBAL hResourceUSECOM = LoadResource(hInst, FindResource(hInst,MAKEINTRESOURCE(IDR_TXT13),"TXT"));
		char* USECOM = (char*)LockResource(hResourceUSECOM);
HGLOBAL hResourceMANDEL = LoadResource(hInst, FindResource(hInst,MAKEINTRESOURCE(IDR_TXT14),"TXT"));
		char* MANDEL = (char*)LockResource(hResourceMANDEL);
HGLOBAL hResourceOPENGL2 = LoadResource(hInst, FindResource(hInst,MAKEINTRESOURCE(IDR_TXT15),"TXT"));
		char* OPENGL2 = (char*)LockResource(hResourceOPENGL2);
HGLOBAL hResourcePE64DEMO = LoadResource(hInst, FindResource(hInst,MAKEINTRESOURCE(IDR_TXT16),"TXT"));
		char* PE64DEMO = (char*)LockResource(hResourcePE64DEMO);
HGLOBAL hResourceTEMPLATE2 = LoadResource(hInst, FindResource(hInst,MAKEINTRESOURCE(IDR_TXT17),"TXT"));
		char* TEMPLATE2 = (char*)LockResource(hResourceTEMPLATE2);
HGLOBAL hResourceUSECOM2 = LoadResource(hInst, FindResource(hInst,MAKEINTRESOURCE(IDR_TXT18),"TXT"));
		char* USECOM2 = (char*)LockResource(hResourceUSECOM2);

struct tabcounter {
	HWND hwndScintilla, Output;
	int strcounter;
	TC_ITEM tabitem;
	string BufferName; /* Имя файла с расширением */
	string FileInfo; /* Полный путь к файлу */
	vector<int> break_points;
};
tabcounter tabNum;
vector<tabcounter> TabNumber; /* Контейнер для содержимого вкладок */

vector<HTREEITEM> ExpState;
vector<HTREEITEM> htreeitem;
vector<string> NameSelInclude;

string api2; /* Строка содержит список функций для автозавершения */
vector<string> api2_name;
vector<string> prototype_api2; /* Вектор содержит прототипы функций */

const int MARK_BOOKMARK = 24;

string equates = " ";
string string_find;
string fortest;

struct AddInc {
	string nameinclude;
	string pathinclude;
};
AddInc NameAddInc;
vector<AddInc> InfInc; /* Контейнер для всех возможных инклудов, содержит имя инклуда и путь к нему */

struct IncludesActiveTab {
	string NameIncludeWithExten; /* Имя инклуда с расширением */
	string PathToTheInclude; /* Путь к инклуду */
	int ID; /* Идентификатор, если ID равен 1, то у инклуда есть родительская папка, если 2, 
				инклуд лежит либо рядом с исходником, либо в папке с компилятором, либо в корне папки INCLUDE */
};
IncludesActiveTab Includes_Active_Tab;
vector<IncludesActiveTab> InvolvedInclude; /* Контейнер содержит задействованные инклуды */

struct DataHtreeitem {
	int Line; /* Номер строки содержащей элемент из списка */
	string NameItem;
};
DataHtreeitem DHtreeitem;
vector<DataHtreeitem> InfoTreeView;

struct iItemTR {
	string iName;
	int iState;
};
iItemTR ItemTR;
vector<iItemTR> Name_Labels; /* Информация о состоянии элемента и его имя */
vector<HTREEITEM> iHTR;

HTREEITEM Inc = (HTREEITEM)TVI_FIRST;
HTREEITEM Include = (HTREEITEM)TVI_FIRST;

static const int LINE_MARGIN_INDEX = 1;
static const int MARGIN_SCRIPT_FOLD_INDEX = 1;
static const int WINDOW_ID = 900;

const char* pCallTipNextWord = NULL;
const char* pCallTipCurDesc = NULL;

RECT rcClient; /* Для ParentWindow */
RECT rcTabControl; /* Для TabControl */
RECT rcREdit; /* Для RichEdit'a */
RECT rcTrV; /* Для TreeView */
RECT rctab; /* Координаты активной вкладки */

Wnd *ParentWindow, *TabControl, *StatusBar, *TabControl_TrV, *AllInc_TrV;
Wnd *HwndScintilla, *Output_N, *TreeView_N, *TreeView_R;
HWND DialogHWND, DialogHWND_2, DialogHWND_3;
HWND Toolbar;

OperationsOnSelectedLines operLines;

TC_ITEM tab_2;

TextRange tr; /* Структура хранит в себе информацию о положении слова, которое вызвало автозавершение */

int iTreeView; /* folder/inc */
int iTray = NULL; /* Состояние трея */
int tN = NULL; /* Счётчик вкладок */
int tmp = NULL;
int tabN;
int counter; /* В эту переменную заносим номер активной вкладки */
int iMemControl = 0; /* для WM_SIZE. Переменная для проверки. Пока переменная равна NULL перерисовки не будет */
int forVerification;
int iInclude = 0;
int i_; /* Номер элемента для удаления */
int Flag_for_the_TreeView = 0; /* Флаг равен единице, если открыт поток обновления дерева */
int Flag_for_the_syntax_highlight = 0; /* Флаг равен единице, если открыт поток подсветки синтаксиса */
int Flag_for_the_Autocompletion = 0;

char buf_in_out[30000]={0}; /* Буфер для вывода */
char buff[10] = {0};
char StrColArray[100]; /* в этот массив будет помещатся все выводимые значения Str и Col в StatusBar  */

string TitleBuf, go_to_the_exe;
string csTemp = "";
string Directory; /* Директория для поиска во вложенных папках */
string OriginalDirectory;
string path_to_the_include; /* Директория для поиска  */
string added_to_the_source_code; /* Текст который будет добавлен в исходный код (include "folder\*.inc" or include "*.inc") */

/* Имена инклудов активной вкладки, которые впоследствии могут быть исключены */
string del_to_the_source_code; /* include "folder\*.inc" */
string del_to_the_source_code_2; /* include "*.inc" */
string del_to_the_source_code_3; /* include 'folder\*.inc' */
string del_to_the_source_code_4; /* include '*.inc' */ 
string del_to_the_source_code_5; /* include 'folder/*.inc' */
string del_to_the_source_code_6; /* include 'folder/*.inc' */
/*****************************************************************************/

/* Структуры для добавления элементов в TreeView */
TV_INSERTSTRUCT insItem;
TVITEM tvitem;
TVITEM iItem;
TV_INSERTSTRUCT isItem;

TVITEM itemEx;

Sci_TextToFind fsci; /* Поиск */

CHARFORMAT cF;
CHARFORMAT chd;
CHARFORMAT forGETCHARFORMAT; /* Для проверки цвета выделенного символа, при покраске */
CHARFORMAT2 chd_2; /* Для подсветки выделенного слова по всему тексту */

CHARRANGE poscur;
CHARRANGE selchar; /* Для подсветки выделенного слова по всему тексту */

POINT poscaret;
POINT pt;

UINT State;

MSG msg;

ReadingIniFile rvalue;

void FileCloseAll(WPARAM Par); /* /File/Close all/ */
void FileSave(); /* /File/Save/ */
void FilePrint(); /* /File/Print/ */
int FileSaveAs(); /* /File/Save as/ */
void FileSaveALL(int to_rem); /* /File/Save all/ */
void FileOpen(); /* Функция открывает файл */
int FileClose(WPARAM wPar); /* Функция закрывает активную вкладку */
void DLGSAVEFILE(); /* Функция вызывает диалог сохранения файла */
void DLGOPENFILE(); /* Функция вызывает диалог открытия файла */
void CloseTab(); /*Функция удаляет активную вкладку и её содержимое.В том чесле удаляется элемент вектора соответствующий
				 номеру удалённой вкладки. Фокус переводится на вкладку с индексом [0].*/
void NewTab(); /* Функция создаёт новую вкладку, переводит на неё фокус и показывает содержимое этой вкладки */
void FileName(); /* Функция получает имя файла с его расширением из пути к файлу */
void InStatusBar(); /* Функция вывода в StatusBar данных */
int PrintFileToPrinter(char* sFileName); /* Функция отправляет открытый файл на печать, на принтер по умолчанию */
void Compile(); /* Компиляция */
void ShowContextMenu(); /* Показывает контекстное меню */
void SetInvVar(); /* Функция создаёт новую переменную окружения для включений*/
void AllIncludes(); /* Всё существующие включения */
void FindFilesInclude(string DirectorySearch, LPCSTR SearchWord ,HTREEITEM Folders); /* DirectorySearch - директория для поиска, SearchWord -что ищем, Folders - дескриптор папки куда добавлять найденное */
HTREEITEM InsItemTreeView(HTREEITEM htreeitem,string tempbuf); /* Добавление нового элемента в TreeView */
HTREEITEM InsItemTreeView_Num2(HTREEITEM htreeitem,string tempbuf);
void UsedIncludes(); /* Отображает в дереве все инклуды привязанные к открытому файлу */
void SearchInDirectory(string DirectorySearch); /* Поиск в определённой директории */
void OpeningFile(string File_Path); /* Открывает файл, принимает путь к файлу */
void DelNew(); /* Освобождение памяти */
void Added_To_The_Source_Code(string Name_Added_Include); /* Добавление Include в исходный код (include "folder\*.inc" or include "*.inc") */
void Remove_From_Source_Code(string str1, string str2, string str3, string str4, string str5, string str6, int num1); /* Удаление (include "folder\*.inc"
																													  or include "*.inc") из исходного кода */
int Overlap(string path_); /* Функция проверяет на совпадение пути файла который пользователь собирается
							открыть с уже открытыми, если будет совпадения файл открыт не будет */

DWORD WINAPI Thread_for_the_TreeView(LPVOID lpVoid); /*Поток для обновления дерева */

BOOL TrayMessage (HWND hDlg, DWORD dwMessage, UINT uID, HICON hIcon, PSTR pszTip); /* Функция помещает иконку приложения в трей */
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void Syntax_Highlight(); /* подсветка синтаксиса */

BOOL CALLBACK MainDlgProc( HWND wnd, UINT msg, WPARAM wParam,LPARAM lParam ); /* Обработчик для диалогов поиска */
void FindDlg(int EDIT, HWND DlghWnd); /* Поиск */
void Find_Replace(); /* Поиск и замена текста для кнопки Rplace all */

void Toggle_a_bookmark(int Line);
void Clear_all_in_the_current_file();
void Clear_all_in_all_files();
void Next_Bookmark();
void Previous_Bookmark();

void Add_Project(char *Name); /* Функция добавляет новый проект */
void Search_in_folder_SDK();
void Inc_();
void MarkersAdd(); /* Функция выствляет маркеры для свёртки текста */
void CodeView(); /* Обозреватель кода */
void AddItemTreeView(HTREEITEM hItem, LPSTR Src); /* Добавление нового элемента к  {"Proc","Labels","Struct","Virtual","Repeat","Import","Include",
												"Interface","Dialog","Macro","Const","Variables","Type"}*/
void Goto(); /* Переход к выбранному элементу в CodeView */

void CloseAllButThis();	/* Функция закрывает все вкладки, кроме активной */
void CloseLeft();	/* Функция закрывает все вкладки слева */
void CloseRight();	/* Функция закрывает все вкладки справа */

LRESULT SendEditor(UINT Msg, WPARAM wParam, LPARAM lParam) 
{
	counter = TabCtrl_GetCurSel(TabControl->hWnd);
		return ::SendMessage(TabNumber[counter].hwndScintilla, Msg, wParam, lParam);
}

HANDLE CProg; /* Мьютекс для запуска единственной копии приложения */ 

static char * breakpoint_rounded_blue_inverted2_xpm[] = {
"16 16 18 1",
" 	c None",
".	c #446D8C",
"+	c #91B5CB",
"@	c #A4D9F1",
"#	c #7DAFCB",
"$	c #4B7694",
"%	c #93B8CE",
"&	c #9FDBF4",
"*	c #7AB0CD",
"=	c #8FD3F1",
"-	c #85CAE8",
";	c #76B8D5",
">	c #65A2BB",
",	c #538AA1",
"'	c #3B6A7D",
")	c #446A86",
"!	c #355E6F",
"~	c #3E6884",
"                ",
"                ",
"                ",
"    .........   ",
"   .+@@@@@@@#$  ",
"  .%&&&&&&&&&*. ",
"  .===========. ",
"  .-----------. ",
"  .;;;;;;;;;;;. ",
"  .>>>>>>>>>>>. ",
"  .,,,,,,,,,,,. ",
"  .'''''''''''. ",
"   )!!!!!!!!!~  ",
"    .........   ",
"                ",
"                "};

/* XPM */
static const char *minus_xpm[] = {
	/* width height num_colors chars_per_pixel */
	"     9     9       16            1",
	/* colors */
	"` c #8c96ac",
	". c #c4d0da",
	"# c #daecf4",
	"a c #ccdeec",
	"b c #eceef4",
	"c c #e0e5eb",
	"d c #a7b7c7",
	"e c #e4ecf0",
	"f c #d0d8e2",
	"g c #b7c5d4",
	"h c #fafdfc",
	"i c #b4becc",
	"j c #d1e6f1",
	"k c #e4f2fb",
	"l c #ecf6fc",
	"m c #d4dfe7",
	/* pixels */
	"hbc.i.cbh",
	"bffeheffb",
	"mfllkllfm",
	"gjkkkkkji",
	"da`````jd",
	"ga#j##jai",
	"f.k##k#.a",
	"#..jkj..#",
	"hemgdgc#h"
};

/* XPM */
static const char *plus_xpm[] = {
	/* width height num_colors chars_per_pixel */
	"     9     9       16            1",
	/* colors */
	"` c #242e44",
	". c #8ea0b5",
	"# c #b7d5e4",
	"a c #dcf2fc",
	"b c #a2b8c8",
	"c c #ccd2dc",
	"d c #b8c6d4",
	"e c #f4f4f4",
	"f c #accadc",
	"g c #798fa4",
	"h c #a4b0c0",
	"i c #cde5f0",
	"j c #bcdeec",
	"k c #ecf1f6",
	"l c #acbccc",
	"m c #fcfefc",
	/* pixels */
	"mech.hcem",
	"eldikille",
	"dlaa`akld",
	".#ii`ii#.",
	"g#`````fg",
	".fjj`jjf.",
	"lbji`ijbd",
	"khb#idlhk",
	"mkd.ghdkm"
};


const char asm_operators[] = " rt byte word dword fword pword qword tbyte tword dqword xword qqword "
								" yword db dw du dd dp df dq dt file dup rb rw rd rp rf rq ";

const char asm_registers[] = " al cl dl bl ah ch dh bh ax cx dx bx sp bp si di eax ecx edx ebx "
							 " esp ebp esi edi es cs ss ds fs gs cr0 cr2 cr3 cr4 dr0 dr1 dr2 dr3 "
							 " dr6 dr7 st0 st1 st2 st3 st4 st5 st6 st7 mm0 mm1 mm2 mm3 mm4 mm5 "
							 " mm6 mm7 xmm0 xmm1 xmm2 xmm3 xmm4 xmm5 xmm6 xmm7 ymm0 ymm1 ymm2 " 
							 " ymm3 ymm4 ymm5 ymm6 ymm7 spl bpl sil dil r8b r9b r10b r11b r12b "
							 " r13b r14b r15b r8w r9w r10w r11w r12w r13w r14w r15w r8d r9d r10d "
							 " r11d r12d r13d r14d r15d rax rcx rdx rbx rsp rbp rsi rdi r8 r9 "
							 " r10 r11 r12 r13 r14 r15 xmm8 xmm9 xmm10 xmm11 xmm12 xmm13 xmm14 "
							 " xmm15 ymm8 ymm9 ymm10 ymm11 ymm12 ymm13 ymm14 ymm15 ";	

const char asm_mnemonics[] = " adc add and bsf bsr bt btc btr bts call cbw clc cld cli cmc cdq cmp cwd cwde dec div "
							 " idiv enter imul inc jmp laxf leave loop loopnz loopne loopz loope mov movsx movzx mul "
							 " neg nop not or pop popa popad popf popfd push pusha pushad pushf pushfd rcl rcr ret retn "
							 " retf rol ror sahf sal sar sbb shl shld shr shrd stc std sti sub test xchg xor jz je jnz "
							 " jne jc jnae jb jnc jae jnb jp jnp js jns jo jno ja jnbe jna jbe jg jnle jge jnl jl jnge "
							 " jle jng jcxz jecxz LODS LODSB LODSW LODSD STOS STOSB STOSW STOSD in out mod rva pushw "
							 " popw bswap popd daa das aaa aas aam retw retnw retfw retd retnd retfd iret iretw iretd "
							 " bound movs movsd cmps cmpsb scas scasw insb ins outs outsw repe rep setne seto cmove "
							 " cmovnc cmpxchg cmpxchg8b ud2 lds pause cpuid lea leave lmsw smsw lgdt lldt sldt ltr str "
							 " lmsw smsw lar lsl verr pushd verw arpl clts lock xadd invlpg rdmsr rdtsc rdpmc wrmsr wbinvd "
							 " rsm sysenter sysexit fld fld1 fldz fldl2t fldl2e fldpi fldlg2 fldln2 fild fst fstp fist "
							 " fistp fbld fbstp fadd faddp fiadd fsub fsubr fmul fdiv fdivr fsubrp fmulp fdivp fdivrp "
							 " fsubp fisub fisubr fimul fidiv fidivr fsqrt fsin fcos frndint fabs f2xm1 fsincos fptan "
							 " fpatan fyl2xp1 fyl2xp1 fyl2xp1 fprem fscale fxtract fxch fnop fcom fcomp fcompp fucom "
							 " fucomp fucompp ficom ficomp fcomi fcomip fucomi fucomip fcmovb ftst fxam fstsw fnstsw "
							 " fstsw fstcw fnstcw fnstcw fnstcw fldcw fldcw fnstenv fnsave frstor finit fninit fclex "
							 " fnclex fstenvw fnstenvw fldenvw fsavew fnsavew frstorw fstenvd fnstenvd fldenvd fsaved "
							 " fnsaved frstord wait fwait ffree fincstp fdecstp movq movd paddb paddw paddd psubb psubw "
							 " psubd paddsb paddsw psubsb psubsw paddusb paddusw psubusb psubusw pmulhw pmullw pmaddwd "
							 " pand por pxor pcmpeqb pcmpeqw pcmpeqd movsb pcmpgtb pcmpgtw pcmpgtd packsswb packssdw "
							 " packuswb punpckhbw punpckhwd punpckhdq punpcklbw punpcklwd punpckldq psllw pslld psllq "
							 " psrlw psrld psrlq psraw psrad emms movaps movups movlps movlhps movmskps movss addps "
							 " addss subps subss mulps mulss divps divss rcpps rcpss sqrtps sqrtss rsqrtps rsqrtss maxps "
							 " maxss minps minss andps andnps orps xorps cmpps cmpltss comiss ucomiss shufps unpckhps "
							 " cvtpi2ps cvtsi2ss cvtps2pi cvttps2pi cvtss2si pextrw pinsrw pavgb pavgw pmaxub pminub "
							 " pmaxsw pminsw pmulhuw psadbw pmovmskb pshufw shufps movntq prefetcht0 prefetcht1 prefetcht2 "
							 " prefetchnta sfence ldmxcsr fxsave fxrstor fxsave movapd movupd movaps movups movlpd movhpd "
							 " movlps movhps movmskpd movmskps movsd addpd addsd subpd subsd mulpd mulsd divpd divsd sqrtpd "
							 " sqrtsd maxpd maxsd minpd minsd andpd andnpd orpd xorpd cmppd cmpsd comisd ucomisd shufpd "
							 " shufps unpckhpd unpcklpd unpckhps unpcklps cvtps2pd cvtpd2ps cvtss2sd cvtsd2ss cvtsd2ss "
							 " cvtpi2pd cvtsi2sd cvtpd2pi cvttpd2pi cvtsd2si cvttsd2si cvtps2dq cvttps2dq movsw pushx "
							 " cvtpd2dq cvttpd2dq cvtdq2ps cvtdq2pd movdqa movdqu movdqa movdqu movq2dq movdq2q pshufw "
							 " pshufhw pshuflw pshufw pshufd pshufw paddq pmuludq pslldq psrldq punpckhqdq punpcklqdq "
							 " movntdq movntpd movnti maskmovdqu clflush lfence mfence sfence lfence fisttp fistp movshdup "
							 " movsldup movddup lddqu addsubps addsubpd haddps haddpd monitor monitor phaddw phaddd phaddsw "
							 " phsubw phsubd pabsb pabsw pabsd pmaddubsw pmulhrsw pshufb psignb psignw psignd palignr "
							 " pavgusb pmulhrw pi2fd pf2id pi2fw pf2iw pfadd pfsub pfsubr pfmul pfacc pfnacc pfpnacc "
							 " pfmax pfmin pswapd pfrcp pfrsqrt pfrcpit1 pfrcp pfrsqit1 pfrsqrt pfrcpit2 pfcmpeq pfcmpge "
							 " pfcmpgt prefetch prefetchw prefetchw prefetch femms rip cmpxchg16b syscall sysret sysexitq "
							 " sysretq rdmsrq wrmsrq pmulld pmuldq pminsb pmaxsb pminuw pmaxuw pminud pmaxud pminsd "
							 " pmaxsd ptest pcmpeqq paskusdw pmovsxbw pmovzxbw pmovsxbd pmovzxbd pmovsxbq pmovzxbq pmovsxwd "
							 " pmovzxwd pmovsxwq pmovzxwq pmovsxdq pmovzxdq phminposuw roundps roundss roundpd roundsd "
							 " dpps dppd mpsadbw roundps blendps blendvps blendpd blendvpd blendps blendpd blendvps "
							 " blendvpd pblendw pblendvb blendps blendvps insertps extractps pinsrb pinsrd pinsrq "
							 " pinsrw pinsrq pextrb pextrw pextrd pextrq pextrq pextrw movntdqa pcmpistri pcmpistrm "
							 " pcmpestri pcmpestrm pcmpgtq pcmpgtq crc32 popcnt popcnt lzcnt extrq insertq movntss movntsd "
							 " vmxoff vmlaunch vmresume vmcall vmptrld vmptrst vmclear vmread vmwrite invept invvpid getsec "
							 " skinit vmrun vmsave vmload vmrun vmmcall stgi clgi invlpga stosb lodsb lodsw ";


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{	

	/* Если запускается второй экземпляр программы */
	CProg = CreateMutex(NULL, false, "JaeEditor");
	if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		HWND hWndRP = FindWindow(NULL, "JaeEditor");
		SetForegroundWindow(hWndRP);
		return 0;
	};

	Search_in_folder_SDK();

	InitCommonControls();

	ParentWindow = new Wnd (WS_EX_ACCEPTFILES, 
							"FRM_TEXTEDIT", 
							"JaeEditor 1.9.15", 
							WS_OVERLAPPEDWINDOW, 
							245,
							55,
							775,
							637, 
							NULL,
							NULL, 
							WindowProc
							);	
	GetClientRect(ParentWindow->hWnd,&rcClient);

	TabControl = new Wnd (WS_EX_OVERLAPPEDWINDOW,
						  WC_TABCONTROLA, 
						  NULL, 
						  WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | 
						  WS_CLIPSIBLINGS | TCS_OWNERDRAWFIXED | TCS_TOOLTIPS,
						  rcClient.left + 175,
						  rcClient.top + 28,
						  rcClient.right - 170,
						  rcClient.bottom - 47,
						  ParentWindow->hWnd,
						  NULL, 
						  NULL
						  );
	GetClientRect(TabControl->hWnd,&rcTabControl);

	/* Создаём первую вкладку */
	tabNum.tabitem.mask = TCIF_TEXT;
	tabNum.tabitem.iImage = -1;
	tabNum.tabitem.pszText = "Untitled";
	TabCtrl_InsertItem(TabControl->hWnd,tN,&tabNum.tabitem); /* Вставляем вкладку в TabControl */
	TabCtrl_SetCurSel(TabControl->hWnd,tN); /* Переводим на неё фокус */
			
	HwndScintilla = new Wnd(0,
							"Scintilla",
							"", 
							WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
							rcTabControl.left + 6,
							rcTabControl.top + 30,
							rcTabControl.right - 10,
							rcTabControl.bottom - 135,
							TabControl->hWnd,
							(HMENU)WINDOW_ID,
							NULL
							);

	tabNum.hwndScintilla = HwndScintilla->hWnd;

	GetClientRect(HwndScintilla->hWnd,&rcREdit);

	Output_N = new Wnd(WS_EX_ACCEPTFILES,
					   "RICHEDIT",
					   NULL,
					   WS_CHILD | WS_VISIBLE  | ES_DISABLENOSCROLL |  WS_VSCROLL |
					   ES_READONLY | ES_LEFT | ES_MULTILINE  | ES_AUTOVSCROLL, 
					   rcTabControl.left + 6,
					   rcREdit.bottom + 47,
					   rcTabControl.right - 10,
					   100,
					   TabControl->hWnd,
					   NULL,
					   NULL
					   );

	tabNum.Output = Output_N->hWnd;
		CHARFORMAT CharF;
		ZeroMemory(&CharF, sizeof(CharF));
		CharF.cbSize = sizeof(CHARFORMAT);
		CharF.dwMask = CFM_SIZE | CFM_FACE | CFM_COLOR | CFM_CHARSET;
		CharF.crTextColor = RGB(72,61,139);
		CharF.bPitchAndFamily = FW_THIN;
		lstrcpy(CharF.szFaceName , "Courier New");
		SendMessage(Output_N->hWnd,EM_SETCHARFORMAT,0,(LPARAM)&CharF);

	tabNum.strcounter = 1;

	TabControl_TrV = new Wnd (WS_EX_OVERLAPPEDWINDOW,
							  WC_TABCONTROLA, 
							  NULL, 
							  WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | 
							  WS_CLIPSIBLINGS | TCS_BOTTOM | TCS_TOOLTIPS,
							  rcClient.left,
							  rcClient.top + 28,
							  178,
							  rcClient.bottom - 48,
							  ParentWindow->hWnd,
							  NULL, 
							  NULL);
	GetClientRect(TabControl_TrV->hWnd,&rcTrV);

	HMODULE hMod = GetModuleHandle(NULL);
	HIMAGELIST himl1 = ImageList_Create(16,16,ILC_COLOR16,3,4);
	HBITMAP hbmp = LoadBitmap(hMod,MAKEINTRESOURCE(IDB_BITMAP34)); 
	ImageList_Add(himl1,hbmp,NULL);
	DeleteObject(hbmp); 
	hbmp = LoadBitmap(hMod,MAKEINTRESOURCE(IDB_BITMAP35));
	ImageList_Add(himl1,hbmp,NULL);
	DeleteObject(hbmp);
	hbmp = LoadBitmap(hMod,MAKEINTRESOURCE(IDB_BITMAP66));
	ImageList_Add(himl1,hbmp,NULL);
	DeleteObject(hbmp);
	TabCtrl_SetImageList(TabControl_TrV->hWnd,himl1);

	tab_2.mask = TCIF_IMAGE;
	tab_2.iImage = 0;
	TabCtrl_InsertItem(TabControl_TrV->hWnd,0,&tab_2); /* Вставляем вкладку в TabControl */
	tab_2.iImage = 1;
	TabCtrl_InsertItem(TabControl_TrV->hWnd,1,&tab_2); /* Вставляем вкладку в TabControl */
	tab_2.iImage = 2;
	TabCtrl_InsertItem(TabControl_TrV->hWnd,2,&tab_2); /* Вставляем вкладку в TabControl */
	TabCtrl_SetMinTabWidth(TabControl_TrV->hWnd,16);

	TreeView_N = new Wnd(NULL,
						 WC_TREEVIEW,
						 NULL,
						 WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_INFOTIP | 
						 TVS_SHOWSELALWAYS,
						 rcTrV.left,
						 rcTrV.top,
						 174,
						 rcTrV.bottom - 26,
						 TabControl_TrV->hWnd,
						 NULL,
						 NULL);

	TreeView_R = new Wnd(NULL,
						 WC_TREEVIEW,
						 NULL,
						 WS_CHILD | WS_VISIBLE  | TVS_LINESATROOT | 
						 TVS_HASBUTTONS | TVS_HASLINES | TVS_INFOTIP | TVS_SHOWSELALWAYS,
						 rcTrV.left,
						 rcTrV.top,
						 174,
						 rcTrV.bottom - 26,
						 TabControl_TrV->hWnd,
						 NULL,
						 NULL);
	TabNumber.push_back(tabNum);

	AllInc_TrV = new Wnd(NULL,
						 WC_TREEVIEW,
						 NULL,
						 WS_CHILD | WS_VISIBLE | TVS_LINESATROOT | 
						 TVS_HASBUTTONS | TVS_HASLINES | TVS_SHOWSELALWAYS,
						 rcTrV.left,
						 rcTrV.top,
						 174,
						 rcTrV.bottom - 26,
						 TabControl_TrV->hWnd,
						 NULL,
						 NULL);
					
	StatusBar = new Wnd (0,
						 STATUSCLASSNAME, 
						 NULL, 
						 WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP,
						 0,
						 0,
						 rcClient.right, 
						 rcClient.bottom,
						 ParentWindow->hWnd,  
						 0, 
						 NULL);

	TrayMessage(ParentWindow->hWnd, 
				NIM_ADD,	
				0, 
				LoadIconA(hInstance,(LPCSTR)IDI_ICON1), 
				ParentWindow->szText);

	TrayMessage(ParentWindow->hWnd, 
				NIM_MODIFY, 
				0, 
				LoadIconA(hInstance,(LPCSTR)IDI_ICON1), 
				ParentWindow->szText); 
		
	SetInvVar();
		
	Syntax_Highlight();

	/* Регистрируем сочетания клавиш */
	RegisterHotKey(ParentWindow->hWnd, ID_KEY_O, MOD_CONTROL, 0x4F); /* Ctrl + O для открытия файла */
	RegisterHotKey(ParentWindow->hWnd, ID_KEY_S, MOD_CONTROL, 0x53);  /* Ctrl + S для сохраниения содержимого активной вкладки */
	RegisterHotKey(ParentWindow->hWnd, ID_KEY_N, MOD_CONTROL, 0x4E);  /* Ctrl + N для создания новой вкладки */
	RegisterHotKey(ParentWindow->hWnd, ID_KEY_P, MOD_CONTROL, 0x50);  /* Ctrl + P для вывода на печать содержимого активной вкладки */
	RegisterHotKey(ParentWindow->hWnd, ID_KEY_SHIFT_S, MOD_CONTROL | MOD_SHIFT, 0x53);  /* Ctrl + Shift + S для сохраниения содержимого всех вкладок */
	RegisterHotKey(ParentWindow->hWnd, ID_KEY_F, MOD_CONTROL, 0x46); /* Find */
	RegisterHotKey(ParentWindow->hWnd, ID_KEY_SHIFT_F, MOD_CONTROL | MOD_SHIFT, 0x46); /* Find and replace */
	RegisterHotKey(ParentWindow->hWnd, ID_KEY_SHIFT_TAB, MOD_SHIFT, 0x09);
	RegisterHotKey(ParentWindow->hWnd, ID_KEY_SHIFT_Q, MOD_CONTROL | MOD_SHIFT, 0x09);
	RegisterHotKey(ParentWindow->hWnd, ID_KEY_SHIFT_C, MOD_CONTROL | MOD_SHIFT, 0x43);
	RegisterHotKey(ParentWindow->hWnd, ID_KEY_SHIFT_X, MOD_CONTROL | MOD_SHIFT, 0x58);

	DragAcceptFiles(ParentWindow->hWnd,true); /* Drag and Drop */
	UsedIncludes();

	Toolbar = CreateWindowEx(NULL, 
							 TOOLBARCLASSNAME, 
							 NULL, 
							 WS_CHILD | TBSTYLE_TRANSPARENT | 
							 TBSTYLE_TOOLTIPS | TBSTYLE_FLAT, 
							 0, 
							 0, 
							 0, 
							 0, 
							 ParentWindow->hWnd, 
							 NULL, 
							 hInstance, 
							 NULL);

	HIMAGELIST hImageList = ImageList_Create(16, 16, ILC_COLOR16 | ILC_MASK, 21, 0);

	HBITMAP newfile        = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP7));
	HBITMAP openfile       = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP44));
	HBITMAP savefile       = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
	HBITMAP saveall        = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP3));
	HBITMAP cut            = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP5));
	HBITMAP copysel        = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP8));
	HBITMAP paste          = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP9));
	HBITMAP decreaseIndent = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP56));
	HBITMAP increaseIndent = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP57));
	HBITMAP undo           = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP4));
	HBITMAP redo           = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP41));
	HBITMAP res1           = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP52));
	HBITMAP res2           = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP53));
	HBITMAP compile        = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP54));
	HBITMAP run            = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP55));
	HBITMAP toggle         = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP58));
	HBITMAP prev           = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP59));
	HBITMAP next           = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP60));
	HBITMAP clearall       = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP62));
	HBITMAP clearcur       = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP61));
	HBITMAP autocompletion = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP63));

	ImageList_Add(hImageList, newfile,        NULL);
	ImageList_Add(hImageList, openfile,       NULL);
	ImageList_Add(hImageList, savefile,       NULL);
	ImageList_Add(hImageList, saveall,        NULL);
	ImageList_Add(hImageList, cut,            NULL);
	ImageList_Add(hImageList, copysel,        NULL);
	ImageList_Add(hImageList, paste,          NULL);
	ImageList_Add(hImageList, decreaseIndent, NULL);
	ImageList_Add(hImageList, increaseIndent, NULL);
	ImageList_Add(hImageList, undo,           NULL);
	ImageList_Add(hImageList, redo,           NULL);
	ImageList_Add(hImageList, res1,           NULL);
	ImageList_Add(hImageList, res2,           NULL);
	ImageList_Add(hImageList, compile,        NULL);
	ImageList_Add(hImageList, run,            NULL);
	ImageList_Add(hImageList, toggle,         NULL);
	ImageList_Add(hImageList, prev,           NULL);
	ImageList_Add(hImageList, next,           NULL);
	ImageList_Add(hImageList, clearall,       NULL);
	ImageList_Add(hImageList, clearcur,       NULL);
	ImageList_Add(hImageList, autocompletion, NULL);

	SendMessage(Toolbar, TB_SETIMAGELIST, 0, (LPARAM)hImageList);

	TBBUTTON tbButtons[21] = 
	{
		{ 0,  IDB_BITMAP7,  TBSTATE_ENABLED, BTNS_AUTOSIZE, TBSTATE_MARKED, 0, 0},
		{ 1,  IDB_BITMAP44, TBSTATE_ENABLED, BTNS_AUTOSIZE, TBSTYLE_BUTTON, 0, 0},
		{ 2,  IDB_BITMAP1,  TBSTATE_ENABLED, BTNS_AUTOSIZE, TBSTYLE_BUTTON, 0, 0},
		{ 3,  IDB_BITMAP3,  TBSTATE_ENABLED, BTNS_AUTOSIZE, TBSTYLE_BUTTON, 0, 0},
		{ 4,  IDB_BITMAP5,  TBSTATE_ENABLED, BTNS_AUTOSIZE, TBSTYLE_BUTTON, 0, 0},
		{ 5,  IDB_BITMAP8,  TBSTATE_ENABLED, BTNS_AUTOSIZE, TBSTYLE_BUTTON, 0, 0},
		{ 6,  IDB_BITMAP9,  TBSTATE_ENABLED, BTNS_AUTOSIZE, TBSTYLE_BUTTON, 0, 0},
		{ 7,  IDB_BITMAP56, TBSTATE_ENABLED, BTNS_AUTOSIZE, TBSTYLE_BUTTON, 0, 0},
		{ 8,  IDB_BITMAP57, TBSTATE_ENABLED, BTNS_AUTOSIZE, TBSTYLE_BUTTON, 0, 0},
		{ 9,  IDB_BITMAP4,  TBSTATE_ENABLED, BTNS_AUTOSIZE, TBSTYLE_BUTTON, 0, 0},
		{ 10, IDB_BITMAP41, TBSTATE_ENABLED, BTNS_AUTOSIZE, TBSTYLE_BUTTON, 0, 0},
		{ 11, IDB_BITMAP52, TBSTATE_ENABLED, BTNS_AUTOSIZE, TBSTYLE_BUTTON, 0, 0},
		{ 12, IDB_BITMAP53, TBSTATE_ENABLED, BTNS_AUTOSIZE, TBSTYLE_BUTTON, 0, 0},
		{ 13, IDB_BITMAP55, TBSTATE_ENABLED, BTNS_AUTOSIZE, TBSTYLE_BUTTON, 0, 0},
		{ 14, IDB_BITMAP39, TBSTATE_ENABLED, BTNS_AUTOSIZE, TBSTYLE_BUTTON, 0, 0},
		{ 15, IDB_BITMAP58, TBSTATE_ENABLED, BTNS_AUTOSIZE, TBSTYLE_BUTTON, 0, 0},
		{ 16, IDB_BITMAP59, TBSTATE_ENABLED, BTNS_AUTOSIZE, TBSTYLE_BUTTON, 0, 0},
		{ 17, IDB_BITMAP60, TBSTATE_ENABLED, BTNS_AUTOSIZE, TBSTYLE_BUTTON, 0, 0},
		{ 18, IDB_BITMAP62, TBSTATE_ENABLED, BTNS_AUTOSIZE, TBSTYLE_BUTTON, 0, 0},
		{ 19, IDB_BITMAP61, TBSTATE_ENABLED, BTNS_AUTOSIZE, TBSTYLE_BUTTON, 0, 0},
		{ 20, IDB_BITMAP63, TBSTATE_ENABLED, BTNS_AUTOSIZE, TBSTYLE_BUTTON, 0, 0}
	}; 

	SendMessage(Toolbar, TB_LOADIMAGES, (WPARAM)IDB_STD_SMALL_COLOR, (LPARAM)HINST_COMMCTRL);

	SendMessage(Toolbar, TB_SETBITMAPSIZE, 0, MAKELONG(16, 16));
	SendMessage(Toolbar, TB_SETBUTTONSIZE, 0, MAKELONG(16, 16));
	SendMessage(Toolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	SendMessage(Toolbar, TB_ADDBUTTONS, (WPARAM)21, (LPARAM)&tbButtons);

	SendMessage(Toolbar, TB_AUTOSIZE, 0, 0);
	ShowWindow(Toolbar, TRUE);

	COLORSCHEME colorsceme;
	colorsceme.dwSize = sizeof(COLORSCHEME);
	colorsceme.clrBtnHighlight = RGB(230,230,250);
	colorsceme.clrBtnShadow = RGB(230,230,250);

	SendMessage(Toolbar,TB_SETCOLORSCHEME,0,(LPARAM)&colorsceme);

	/* Открываем файлы, которые были в программе до её закрытия */
	int sectionS = rvalue.GetSectionSize("opened");
	if(sectionS != 0)
	{
		for(int i = 0; i < sectionS; i++)
		{
			if(rvalue.GetOpenedFile(std::to_string(i)).size() != 0) OpeningFile(rvalue.GetOpenedFile(std::to_string(i)));
		}
		rvalue.ClearSection("opened");
	}

	/* Открытие файла, вызвавшего открытие программы */
	if(lstrlen(lpCmdLine) != 0)
	{
		string paramLine;
		int s_f = 0;
		string str_f = lpCmdLine;
		while(s_f = str_f.find(".asm"))
		{
			if(s_f != string::npos)
			{
				paramLine = str_f.substr(0, s_f + 4);
				str_f.erase(0, s_f + 5);
				while(paramLine[0] == 34 || paramLine[0] == 32)
				{
					paramLine.erase(0, 1);
				}
				OpeningFile(paramLine);
			}
			else
			{
				break;
			}
		}
	}

	iMemControl = 1000; /* для WM_SIZE. В x64 работает без проверки, в x86 только с проверкой */
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		HWND ActiveWindow = GetForegroundWindow();
		if(ActiveWindow == ParentWindow->hWnd)
		{
			counter = TabCtrl_GetCurSel(TabControl->hWnd);
			if(msg.message == WM_HOTKEY && msg.wParam == ID_KEY_SHIFT_F)
			{
				/* Чтобы обеспечить нормальную работу диалогов, не позволяем открывать два диалого одновременно */
				if(DialogHWND != 0) DestroyWindow(DialogHWND);
				if(DialogHWND_2 != 0) DestroyWindow(DialogHWND_2);
				DialogHWND_2 = CreateDialog(NULL,MAKEINTRESOURCE(IDD_DIALOG2),ParentWindow->hWnd,MainDlgProc); 
				ShowWindow(DialogHWND_2, SW_SHOWNORMAL);
			}
			if(msg.message == WM_HOTKEY && msg.wParam == ID_KEY_F)
			{
				/* Чтобы обеспечить нормальную работу диалогов, не позволяем открывать два диалого одновременно */
				if(DialogHWND_2 != 0) DestroyWindow(DialogHWND_2);
				if(DialogHWND != 0) DestroyWindow(DialogHWND);
				DialogHWND = CreateDialog(NULL,MAKEINTRESOURCE(IDD_DIALOG1),ParentWindow->hWnd,MainDlgProc); 
				ShowWindow(DialogHWND, SW_SHOWNORMAL);
			}
			if(msg.message == WM_HOTKEY  && msg.wParam == ID_KEY_SHIFT_C)
			{
				counter = TabCtrl_GetCurSel(TabControl->hWnd);
				operLines.CommentOutTheSelectedLines(TabNumber[counter].hwndScintilla);
			}
			if(msg.message == WM_HOTKEY  && msg.wParam == ID_KEY_SHIFT_X) 
			{
				counter = TabCtrl_GetCurSel(TabControl->hWnd);
				operLines.UncommentTheSelectedLines(TabNumber[counter].hwndScintilla);
			}
			if(msg.message == WM_HOTKEY  && msg.wParam == ID_KEY_SHIFT_TAB) 
			{
				counter = TabCtrl_GetCurSel(TabControl->hWnd);
				operLines.IncreaseIndent(TabNumber[counter].hwndScintilla);
			}
			if(msg.message == WM_HOTKEY  && msg.wParam == ID_KEY_SHIFT_Q) 
			{
				counter = TabCtrl_GetCurSel(TabControl->hWnd);
				operLines.DecreaseIndent(TabNumber[counter].hwndScintilla);
			}
			if(msg.message == WM_HOTKEY  && msg.wParam == ID_KEY_O) FileOpen();
			if(msg.message == WM_HOTKEY  && msg.wParam == ID_KEY_S) FileSave();
			if(msg.message == WM_HOTKEY  && msg.wParam == ID_KEY_N) NewTab();
			if(msg.message == WM_HOTKEY  && msg.wParam == ID_KEY_P) FilePrint();
			if(msg.message == WM_HOTKEY  && msg.wParam == ID_KEY_SHIFT_S) FileSaveALL(counter);;
			if(msg.message == WM_KEYDOWN && msg.wParam == VK_F8) {
				Compile();
				SetWindowText(TabNumber[counter].Output,csTemp.c_str());
			}
			if(msg.message == WM_KEYDOWN && msg.wParam == VK_F9) {
				Compile();
				ShellExecute(NULL, "open", go_to_the_exe.c_str(), NULL, NULL, SW_SHOWNORMAL);
				SetWindowText(TabNumber[counter].Output,csTemp.c_str());
			}	
			if(msg.message == WM_RBUTTONUP) ShowContextMenu();
			if(msg.message == WM_KEYDOWN && (msg.wParam == '\b' || msg.wParam == 46))
			{
				sort(TabNumber[counter].break_points.begin(), TabNumber[counter].break_points.end());
				/* Проверка закладок выставленных и сохранённых в векторе */
				int curPos = SendEditor(SCI_GETCURRENTPOS,0,0);
				int curLine = SendEditor(SCI_LINEFROMPOSITION,curPos,0);
				//curLine--;
				for(int i = 0; i < TabNumber[counter].break_points.size(); i++)
				{
					if(curLine < TabNumber[counter].break_points.at(i))
					{
						TabNumber[counter].break_points.at(i) = TabNumber[counter].break_points.at(i) - 1;
					}
				}
			}
		}
	}
	return (int) msg.wParam;
}

/* Обработчик для диалогов */
BOOL CALLBACK MainDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message) 
	{
	case WM_INITDIALOG: 
		return true;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON3: FindDlg(IDC_EDIT1,DialogHWND_2); return true; /* Простой поиск для диалога Find and replace */
		case IDC_BUTTON4: /* Замена для диалога Find and replace */
		{
			int len = SendDlgItemMessage(DialogHWND_2,IDC_EDIT1,WM_GETTEXTLENGTH,0,0);
			len++;
			char* farr = new char[len];
			ZeroMemory(farr,len);
			if(farr)
			{
				int farr_i = SendEditor(SCI_GETSELTEXT,0,(LPARAM)farr);
				if(farr_i != 0)
				{
					len = SendDlgItemMessage(DialogHWND_2,IDC_EDIT2,WM_GETTEXTLENGTH,0,0);
					if(len != 0)
					{
						len++;
						char* farr_ = new char[len];
						ZeroMemory(farr_,len);
						if(farr_)
						{
							GetDlgItemText(DialogHWND_2,IDC_EDIT2,farr_,len);
							SendEditor(SCI_REPLACESEL,0,(LPARAM)farr_);
						}
						delete[] farr_;
					}
				} 
				else
				{
					HWND dlg = FindWindow(NULL,"Find text");
					if(dlg != 0) DestroyWindow(dlg);
					FindDlg(IDC_EDIT1,DialogHWND_2);
					farr_i = SendEditor(SCI_GETSELTEXT,0,(LPARAM)farr);
					if(farr_i != 0) {
						len = SendDlgItemMessage(DialogHWND_2,IDC_EDIT2,WM_GETTEXTLENGTH,0,0);
						if(len != 0) 
						{
							len++;
							char* farr_ = new char[len];
							ZeroMemory(farr_,len);
							if(farr_) 
							{
								GetDlgItemText(DialogHWND_2,IDC_EDIT2,farr_,len);
								SendEditor(SCI_REPLACESEL,0,(LPARAM)farr_);
							}
							delete[] farr_;
						}
					}
				}
			}
			delete[] farr;
			return true;
		}
		case IDC_BUTTON5: Find_Replace(); return true; /* кнопка Replace all для диалога Find and replace */
		case IDC_BUTTON1:
		{
			if(hwnd == DialogHWND_3) DestroyWindow(DialogHWND_3);
			else FindDlg(IDC_EDIT1,DialogHWND);
			return true; /* Поиск для диалога Find */
		}
		}
		return true;
	case WM_CLOSE:
		string_find.clear();
		EndDialog(DialogHWND, wParam); 
		EndDialog(DialogHWND_2, wParam); 
		return true;
	}
	return FALSE;
}

/* Поиск и замена текста для кнопки Replace all */
void Find_Replace()
{
	int flaf = 0;
	UINT BST = IsDlgButtonChecked(DialogHWND_2, IDC_CHECK1);
	if(BST == 1)
	{
		flaf = SCFIND_MATCHCASE | SCFIND_WHOLEWORD;
	} 
	else
	{
		flaf = SCFIND_MATCHCASE;
	}
	HWND dlg = FindWindow(NULL,"Find text");
	if(dlg != 0) DestroyWindow(dlg);
	int len = SendDlgItemMessage(DialogHWND_2,IDC_EDIT1,WM_GETTEXTLENGTH,0,0);
	len++;
	char* farr = new char[len];
	if(farr)
	{
		int tlen = SendEditor(SCI_GETTEXTLENGTH,0,0);
		GetDlgItemText(DialogHWND_2,IDC_EDIT1,farr,len);
		fsci.lpstrText = farr;
		fsci.chrg.cpMin = 0;
		fsci.chrg.cpMax = tlen;
		int result_find;
		do
		{
			result_find = SendEditor(SCI_FINDTEXT,flaf,(LPARAM)&fsci);
			if(result_find != -1)
			{
				SendEditor(SCI_SETSEL,fsci.chrgText.cpMin,fsci.chrgText.cpMax);
				len = SendDlgItemMessage(DialogHWND_2,IDC_EDIT2,WM_GETTEXTLENGTH,0,0);
				if(len != 0)
				{
					len++;
					char* farr_ = new char[len];
					ZeroMemory(farr_,len);
					if(farr_)
					{
						GetDlgItemText(DialogHWND_2,IDC_EDIT2,farr_,len);
						SendEditor(SCI_REPLACESEL,0,(LPARAM)farr_);
					}
					fsci.chrg.cpMin = fsci.chrgText.cpMin + 1;
					fsci.chrg.cpMax = fsci.chrg.cpMax + len;
					delete[] farr_;
				}
			}
		} while (result_find != -1);
	}
	delete[] farr;
}

/* Поиск */
void FindDlg(int EDIT, HWND DlghWnd)
{
	int flaf = 0;
	UINT BST = IsDlgButtonChecked(DlghWnd, IDC_CHECK1);
	if(BST == 1)
	{
		flaf = SCFIND_MATCHCASE | SCFIND_WHOLEWORD;
	} 
	else
	{
		flaf = SCFIND_MATCHCASE;
	}
	HWND dlg = FindWindow(NULL,"Find text");
	if(dlg != 0) DestroyWindow(dlg);
	int len = SendDlgItemMessage(DlghWnd,EDIT,WM_GETTEXTLENGTH,0,0);
	len++;
	char* farr = new char[len];
	if(farr)
	{
		int tlen = SendEditor(SCI_GETTEXTLENGTH,0,0);
		GetDlgItemText(DlghWnd,EDIT,farr,len);
		fortest = farr;
		if(string_find != fortest || string_find.size() == 0)
		{ 
			string_find = farr;
			fsci.chrg.cpMin = 0;
			fsci.chrg.cpMax = tlen;
		}
		else
		{
			string_find = farr;
			fsci.chrg.cpMin = fsci.chrgText.cpMax;
			fsci.chrg.cpMax = tlen;
		}
		fsci.lpstrText = farr;
		int result_find = SendEditor(SCI_FINDTEXT,flaf,(LPARAM)&fsci);
		if(result_find == -1)
		{
			MessageBox(ParentWindow->hWnd,"Can't find the text","Find text",MB_OK);
			string_find.clear();
		} 
		else
		{
			SendEditor(SCI_SETSEL,fsci.chrgText.cpMin,fsci.chrgText.cpMax);
		}
	}
	delete[] farr;
}

/* Всё существующие включения активной вкладки */
void UsedIncludes()
{
	counter = TabCtrl_GetCurSel(TabControl->hWnd);
	TreeView_DeleteAllItems(TreeView_N->hWnd);
	InfInc.clear();

	/* Загрузка массива изображений для TreeView */
	HMODULE hMod = GetModuleHandle(NULL);
	HIMAGELIST himl2 = ImageList_Create(16,16,ILC_COLOR16,2,4);
	HBITMAP TrV = LoadBitmap(hMod,MAKEINTRESOURCE(IDB_BITMAP36)); 
	ImageList_Add(himl2,TrV,NULL);
	DeleteObject(TrV); 
	TrV = LoadBitmap(hMod,MAKEINTRESOURCE(IDB_BITMAP37)); 
	ImageList_Add(himl2,TrV,NULL);
	DeleteObject(TrV);
	TrV = LoadBitmap(hMod,MAKEINTRESOURCE(IDB_BITMAP38)); 
	ImageList_Add(himl2,TrV,NULL);
	DeleteObject(TrV);
	TreeView_SetImageList(TreeView_N->hWnd,himl2,TVSIL_NORMAL);

	ZeroMemory(&iItem,sizeof(TVITEM));
	ZeroMemory(&isItem,sizeof(TV_INSERTSTRUCT));
	iItem.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM | TVIF_CHILDREN;
	iItem.pszText = "INCLUDE";
	iItem.cChildren = 1;
	iItem.iImage = 0;
	iItem.iSelectedImage = 0;
	isItem.hParent = NULL;
	isItem.hInsertAfter = TVI_ROOT;
	isItem.item = iItem;
	Inc = TreeView_InsertItem(TreeView_N->hWnd,&isItem); /* Вставка элемента в TreeView */

	WIN32_FIND_DATA w32fd;
	memset(&w32fd,0,sizeof(WIN32_FIND_DATA));
	char f_path[150] = {0};
	GetModuleFileName(NULL,f_path,150); /* Получаем полный путь к исполняемому файлу, т.к. в той же папке лежит папка INCLUDE */
	string f_p;

	//////////////////////////////////// Поиск в папке с исходником //////////////////////////////////
	if(TabNumber[counter].FileInfo.size() != 0)
	{ //Если файл не сохранён, директории для поиск не может быть
		f_p = TabNumber[counter].FileInfo;
		int p_exe = f_p.rfind("\\");
		f_p.erase(p_exe+1,f_p.length());
		SetCurrentDirectory(f_p.c_str());
		HANDLE findinclude_2 = FindFirstFile("*.inc",&w32fd);
		do 
		{
			if(w32fd.nFileSizeLow != 0) 
			{
				string path_to_the_inc;
				path_to_the_inc = f_p;
				path_to_the_inc += w32fd.cFileName;
				NameAddInc.pathinclude = path_to_the_inc;
				NameAddInc.nameinclude = w32fd.cFileName;
				InfInc.push_back(NameAddInc);
			}
		} while (FindNextFile(findinclude_2,&w32fd));
		FindClose(findinclude_2);
	}
	//////////////////////////////////// Поиск в папке с компилятором //////////////////////////////////
	f_p = f_path;
	int p_exe_2 = f_p.rfind("\\");
	f_p.erase(p_exe_2+1,f_p.length());
	SetCurrentDirectory(f_p.c_str());
	HANDLE findinclude = FindFirstFile("*.inc",&w32fd);
	do
	{
		int fl = 0;
		for(int num = 0; num < InfInc.size(); num++)
		{
			string path_to_the_inc;
			path_to_the_inc = f_p;
			path_to_the_inc += w32fd.cFileName;
			if(w32fd.cFileName == InfInc[num].nameinclude && path_to_the_inc == InfInc[num].pathinclude)
			{
				fl = 1;
			}
		}
		if(fl != 1 && w32fd.nFileSizeLow != 0)
		{
			string path_to_the_inc;
			path_to_the_inc = f_p;
			path_to_the_inc += w32fd.cFileName;
			NameAddInc.pathinclude = path_to_the_inc;
			NameAddInc.nameinclude = w32fd.cFileName;
			InfInc.push_back(NameAddInc);
		}
	} while (FindNextFile(findinclude,&w32fd));
	FindClose(findinclude);

	//////////////////////////////////// Поиск в папке Include //////////////////////////////////
	f_p = f_path;
	int p_exe_3 = f_p.rfind("\\");
	f_p.erase(p_exe_3+1,f_p.length());
	f_p += "INCLUDE\\";
	SearchInDirectory(f_p.c_str());

	/////////////////// Проверка на наличие инклудов в тексте //////////////////////////////////
	int textlenght = SendMessage(TabNumber[counter].hwndScintilla,SCI_GETTEXTLENGTH,0,0);
	InvolvedInclude.clear();
	Includes_Active_Tab.ID = 0;
	Includes_Active_Tab.NameIncludeWithExten = "";
	Includes_Active_Tab.PathToTheInclude = "";
	InvolvedInclude.push_back(Includes_Active_Tab); /* Если инклуд добавили в дерево, добавляем информацию о нём в вектор */
	if(textlenght != 0)
	{
		char* textinRE = new char[textlenght+1];
		if(textinRE)
		{
			string txt_;
			SendEditor(SCI_GETTEXT,textlenght+1,(LPARAM)textinRE);
			strupr(textinRE); /* Поиск будет в верхнем регистре */
			txt_ = textinRE;

			/* Поиск в тексте строк вида ("*.inc) и ('*.inc), строки в верхнем регистре */
			for(int count = 0; count < InfInc.size(); count++)
			{
				int checkup_ = 0;
				for(int ch_1 = 0; ch_1 < InvolvedInclude.size(); ch_1++)
				{
					if((InfInc[count].nameinclude == InvolvedInclude[ch_1].NameIncludeWithExten && InvolvedInclude[ch_1].ID != 2) 
						|| (InfInc[count].nameinclude != InvolvedInclude[ch_1].NameIncludeWithExten && InvolvedInclude[ch_1].ID != 1))
					{
						string f_word = InfInc[count].nameinclude;
						char etr[100] = {0};
						strcpy(etr,f_word.c_str());
						strupr(etr);
						f_word = "\'";
						f_word += etr;
						int found = txt_.find(f_word);
						if(found != -1) { //////////////////////
							checkup_++;
							continue;
						}
						f_word = "\"";
						f_word += etr;
						found = txt_.find(f_word);
						if(found != -1) { /////////////////////////
							checkup_++;
						}
					}
				}
				if(checkup_ == InvolvedInclude.size())
				{
					iTreeView = 2;
					InsItemTreeView_Num2(Inc,InfInc[count].nameinclude);
					Includes_Active_Tab.ID = 2;
					Includes_Active_Tab.NameIncludeWithExten = InfInc[count].nameinclude;
					Includes_Active_Tab.PathToTheInclude = InfInc[count].pathinclude;
					InvolvedInclude.push_back(Includes_Active_Tab); /* Если инклуд добавили в дерево, добавляем информацию о нём в вектор */
				}
			}
			/* Поиск строк вида (folder\*.inc), строки также в верхнем регистре */
			for(int count = 0; count < InfInc.size(); count++)
			{
				string fold = InfInc[count].pathinclude;
				int pos_s = fold.rfind("\\");
				fold.erase(pos_s,InfInc[count].pathinclude.length());
				pos_s = fold.rfind("\\");
				fold.erase(0,pos_s + 1);
				string f_word = fold;
				f_word += "\\";
				f_word += InfInc[count].nameinclude;
				char etr[100] = {0};
				strcpy(etr,f_word.c_str());
				strupr(etr);
				f_word = etr;
				int found = txt_.find(f_word);
				if(found != -1)
				{
					iTreeView = 2;
					InsItemTreeView_Num2(Inc,InfInc[count].nameinclude);
					Includes_Active_Tab.ID = 1;
					Includes_Active_Tab.NameIncludeWithExten = InfInc[count].nameinclude;
					Includes_Active_Tab.PathToTheInclude = InfInc[count].pathinclude;
					InvolvedInclude.push_back(Includes_Active_Tab); /* Если инклуд добавили в дерево, добавляем информацию о нём в вектор */
				}
			}
			/* Поиск строк вида (folder/*.inc), строки также в верхнем регистре */
			for(int count = 0; count < InfInc.size(); count++)
			{
				string fold = InfInc[count].pathinclude;
				int pos_s = fold.rfind("\\");
				fold.erase(pos_s,InfInc[count].pathinclude.length());
				pos_s = fold.rfind("\\");
				fold.erase(0,pos_s + 1);
				string f_word = fold;
				f_word += "/";
				f_word += InfInc[count].nameinclude;
				char etr[100] = {0};
				strcpy(etr,f_word.c_str());
				strupr(etr);
				f_word = etr;
				int found = txt_.find(f_word);
				if(found != -1)
				{
					iTreeView = 2;
					InsItemTreeView_Num2(Inc,InfInc[count].nameinclude);
					Includes_Active_Tab.ID = 1;
					Includes_Active_Tab.NameIncludeWithExten = InfInc[count].nameinclude;
					Includes_Active_Tab.PathToTheInclude = InfInc[count].pathinclude;
					InvolvedInclude.push_back(Includes_Active_Tab); /* Если инклуд добавили в дерево, добавляем информацию о нём в вектор */
				}
			}
		}
		delete[] textinRE;
	}
	/* Параметры текста элемента в TreeView */
	TreeView_SetTextColor(TreeView_N->hWnd,RGB(71,60,139));
	TreeView_SetLineColor(TreeView_N->hWnd,RGB(71,60,139));
	TreeView_Expand(TreeView_N->hWnd,Inc,TVM_EXPAND);
}

/* Поиск инклудов в переменных окружения */
void SearchInDirectory(string DirectorySearch)
{
	WIN32_FIND_DATA wfd;
	memset(&wfd,0,sizeof(WIN32_FIND_DATA));
	string FileName_Inc;
	SetCurrentDirectory(DirectorySearch.c_str());
	HANDLE findinclude_3 = FindFirstFile("*.*",&wfd);
	do 
	{
		FileName_Inc = wfd.cFileName;
		string CopyDir;
		if((FileName_Inc != ".") 
			&& (FileName_Inc != "..") 
			&& ((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
			== FILE_ATTRIBUTE_DIRECTORY)) 
		{
			CopyDir = DirectorySearch;
			CopyDir += FileName_Inc;
			CopyDir += "\\";
			SearchInDirectory(CopyDir.c_str());
		} 
		else if((FileName_Inc != ".") 
				&& (FileName_Inc != "..") 
				&& ((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
				!= FILE_ATTRIBUTE_DIRECTORY))
		{
			int fl = 0;
			for(int num = 0; num < InfInc.size(); num++)
			{
				string path_to_the_inc;
				path_to_the_inc = DirectorySearch;
				path_to_the_inc += FileName_Inc;
				if(wfd.cFileName == InfInc[num].nameinclude && path_to_the_inc == InfInc[num].pathinclude)
				{
					fl = 1;
				}
			}
			if(fl != 1)
			{
				string path_to_the_inc;
				path_to_the_inc = DirectorySearch;
				path_to_the_inc += FileName_Inc;
				NameAddInc.pathinclude = path_to_the_inc;
				NameAddInc.nameinclude = FileName_Inc;
				InfInc.push_back(NameAddInc);
			}
		}
	} 
	while (FindNextFile(findinclude_3,&wfd));
	FindClose(findinclude_3);
}

/* DirectorySearch - директория для поиска, SearchWord - что ищем, Folders - дескриптор папки куда добавлять найденное */
void FindFilesInclude(string DirectorySearch, LPCSTR SearchWord ,HTREEITEM Folders)
{
	WIN32_FIND_DATA wfd;
	memset(&wfd,0,sizeof(WIN32_FIND_DATA));
	string FileName_Inc;
	SetCurrentDirectory(DirectorySearch.c_str());
	HANDLE hfind = FindFirstFile(SearchWord,&wfd);
	do 
	{
		FileName_Inc = wfd.cFileName;
		if((FileName_Inc != ".") 
			&& (FileName_Inc != "..") 
			&& ((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
			== FILE_ATTRIBUTE_DIRECTORY)) 
		{
			iTreeView = 1; 
			string CopyDir;
			CopyDir = DirectorySearch;
			CopyDir += FileName_Inc;
			CopyDir += "\\";
			HTREEITEM hINC = InsItemTreeView(Folders,wfd.cFileName);
			htreeitem.push_back(hINC);
			FindFilesInclude(CopyDir.c_str(),SearchWord,hINC);
		} 
		else if((FileName_Inc != ".") 
				&& (FileName_Inc != "..") 
				&& ((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
				!= FILE_ATTRIBUTE_DIRECTORY)) 
		{
			iTreeView = 2;
			InsItemTreeView(Folders,wfd.cFileName);
		}
	} while (FindNextFile(hfind,&wfd));
	FindClose(hfind);
}

/* Добавление нового элемента в TreeView для первой вкладки */
HTREEITEM InsItemTreeView_Num2(HTREEITEM htreeitem,string tempbuf)
{
	counter = TabCtrl_GetCurSel(TabControl->hWnd);
	ZeroMemory(&iItem,sizeof(TVITEM));
	ZeroMemory(&isItem,sizeof(TV_INSERTSTRUCT));
	if(iTreeView == 1)
	{
		iItem.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_CHILDREN;
		iItem.iImage = 1;
		iItem.iSelectedImage = 1;
		isItem.hInsertAfter = TVI_FIRST;
		iItem.cChildren = 1;
	} 
	else
	{
		iItem.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
		iItem.iImage = 2;
		iItem.iSelectedImage = 2;
		isItem.hInsertAfter = TVI_LAST;
	}
	const char* tempstr = tempbuf.c_str();
	iItem.pszText = (LPSTR)tempstr;
	if(htreeitem == 0)
	{
		isItem.hParent = Inc;
	}
	else
	{
		isItem.hParent = htreeitem;
	}
	isItem.item = iItem;
	return TreeView_InsertItem(TreeView_N->hWnd,&isItem);
}

/* Добавление нового элемента в TreeView для второй вкладки */
HTREEITEM InsItemTreeView(HTREEITEM htreeitem,string tempbuf)
{
	ZeroMemory(&tvitem,sizeof(TVITEM));
	ZeroMemory(&insItem,sizeof(TV_INSERTSTRUCT));
	if(iTreeView == 1)
	{
		tvitem.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_CHILDREN;
		tvitem.iImage = 1;
		tvitem.iSelectedImage = 1;
		insItem.hInsertAfter = TVI_FIRST;
		tvitem.cChildren = 1;
	} 
	else
	{
		tvitem.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
		tvitem.iImage = 2;
		tvitem.iSelectedImage = 2;
		insItem.hInsertAfter = TVI_LAST;
	}
	const char* tempstr = tempbuf.c_str();
	tvitem.pszText = (LPSTR)tempstr;
	if(htreeitem == 0)
	{
		insItem.hParent = Include;
	} 
	else
	{
		insItem.hParent = htreeitem;
	}
	insItem.item = tvitem;
	return TreeView_InsertItem(AllInc_TrV->hWnd,&insItem);
}

/* Обозреватель кода */
void CodeView()
{
	counter = TabCtrl_GetCurSel(TabControl->hWnd);
	if(iHTR.size() != 0)
	{
		Name_Labels.clear();
		ZeroMemory(&iItem,sizeof(TVITEM));
		iItem.mask = TVIS_EXPANDED;
		for(int i = 0; i < 10; i++)
		{
			int iState = TreeView_GetItemState(TreeView_R->hWnd,iHTR[i],&iItem);
			if(iState == 96 || iState == 98)
			{
				ItemTR.iState = 1;
				ZeroMemory(&iItem,sizeof(TVITEM));
				iItem.mask = TVIF_TEXT;
				char etr[100]={0};
				iItem.pszText=etr;
				iItem.cchTextMax=100;
				iItem.hItem = iHTR[i];
				TreeView_GetItem(TreeView_R->hWnd,&iItem);
				ItemTR.iName = iItem.pszText;
				Name_Labels.push_back(ItemTR);
			}
		}
	}
	
	TreeView_DeleteAllItems(TreeView_R->hWnd);
	/* Загрузка массива изображений для TreeView */
	HMODULE hMod = GetModuleHandle(NULL);
	HIMAGELIST himl2 = ImageList_Create(16,16,ILC_COLOR16,2,4);
	HBITMAP TrV = LoadBitmap(hMod,MAKEINTRESOURCE(IDB_BITMAP65)); 
	ImageList_Add(himl2,TrV,NULL);
	DeleteObject(TrV); 
	TrV = LoadBitmap(hMod,MAKEINTRESOURCE(IDB_BITMAP64)); 
	ImageList_Add(himl2,TrV,NULL);
	DeleteObject(TrV); 
	TrV = LoadBitmap(hMod,MAKEINTRESOURCE(IDB_BITMAP67)); 
	ImageList_Add(himl2,TrV,NULL);
	DeleteObject(TrV); 
	TreeView_SetImageList(TreeView_R->hWnd,himl2,TVSIL_NORMAL);

	ZeroMemory(&iItem,sizeof(TVITEM));
	ZeroMemory(&isItem,sizeof(TV_INSERTSTRUCT));
	iItem.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM | TVIF_CHILDREN;
	if(TabNumber[counter].BufferName.size() != 0)
	{
		char NameCurrentTab[100] = {0};
		strcpy(NameCurrentTab,TabNumber[counter].BufferName.c_str());
		iItem.pszText = NameCurrentTab;
	} 
	else
	{
		iItem.pszText = "Untitled";
	}	
	iItem.cChildren = 1;
	iItem.iImage = 0;
	iItem.iSelectedImage = 0;
	isItem.hParent = NULL;
	isItem.hInsertAfter = TVI_ROOT;
	isItem.item = iItem;
	HTREEITEM NameASM = TreeView_InsertItem(TreeView_R->hWnd,&isItem); /* Вставка элемента в TreeView */

	iHTR.clear();
	const char* NameLabels[] = {"Proc","Labels","Struct","Virtual","Repeat","Import","Include","Dialog","Macro","Const"};
	for(int i = 0; i < 10; i++)
	{
		ZeroMemory(&iItem,sizeof(TVITEM));
		ZeroMemory(&isItem,sizeof(TV_INSERTSTRUCT));
		iItem.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_CHILDREN;
		iItem.iImage = 1;
		iItem.iSelectedImage = 1;
		isItem.hInsertAfter = TVI_FIRST;
		iItem.cChildren = 1;
		iItem.pszText = (LPSTR)NameLabels[i];
		insItem.hParent = NameASM;
		insItem.item = iItem;
		HTREEITEM var = TreeView_InsertItem(TreeView_R->hWnd,&insItem);
		iHTR.push_back(var);
	}

	int iTextLength = SendEditor(SCI_GETTEXTLENGTH,0,0) + 1;
	char* iText = new char[iTextLength];
	if(iText)
	{
		ZeroMemory(iText,iTextLength);
		int iCount = SendEditor(SCI_GETLINECOUNT,0,0);
		for(int i = 0; i < iCount; i++) {
			SendEditor(SCI_GETLINE,i,(LPARAM)iText);
			string S_str = iText;
			char str[300] = {0};

			int sc = sscanf_s(iText,"	proc %[^,]",str,300);
			if(sc!=-1 && sc!=0) {
				AddItemTreeView(iHTR[0], str); /* Proc */
				DHtreeitem.NameItem = str;
				DHtreeitem.Line = i;
				InfoTreeView.push_back(DHtreeitem);
			}

			sc = sscanf_s(iText,"	 include %s",str,300);
			if(sc!=-1 && sc!=0)
			{
				AddItemTreeView(iHTR[6], str); /* Includes */
				DHtreeitem.NameItem = str;
				DHtreeitem.Line = i;
				InfoTreeView.push_back(DHtreeitem);
			}

			sc = sscanf_s(iText,"	INCLUDE %s",str,300);
			if(sc!=-1 && sc!=0) {
				AddItemTreeView(iHTR[6], str); /* Includes */
				DHtreeitem.NameItem = str;
				DHtreeitem.Line = i;
				InfoTreeView.push_back(DHtreeitem);
			}

			sc = sscanf_s(iText,"	Include %s",str,300);
			if(sc!=-1 && sc!=0)
			{
				AddItemTreeView(iHTR[6], str); /* Includes */
				DHtreeitem.NameItem = str;
				DHtreeitem.Line = i;
				InfoTreeView.push_back(DHtreeitem);
			}

			sc = sscanf_s(iText,"	 struct %s",str,300);
			if(sc!=-1 && sc!=0)
			{
				AddItemTreeView(iHTR[2], str); /* Struct */
				DHtreeitem.NameItem = str;
				DHtreeitem.Line = i;
				InfoTreeView.push_back(DHtreeitem);
			}

			sc = S_str.find(":"); 
			if(sc!=-1)
			{	
				for(int iT = 0; iT < S_str.size(); iT++)
				{
					if(S_str[iT] == 32 || S_str[iT] == 9)
					{
						 S_str.erase(iT,1);
						 iT--;
					}
				}
				if(S_str.find(" ") == -1 && S_str.find("'") == -1 && S_str.find(";") == -1 && S_str.find(",") == -1)
				{
					AddItemTreeView(iHTR[1], (LPSTR)S_str.c_str()); /* Labels */
					DHtreeitem.NameItem = S_str;
					DHtreeitem.Line = i;
					InfoTreeView.push_back(DHtreeitem);
				}
			}

			sc = sscanf_s(iText,"	repeat %s",str,300);
			if(sc!=-1 && sc!=0)
			{
				string iSea = "repeat ";
				iSea += str;
				AddItemTreeView(iHTR[4], (LPSTR)iSea.c_str()); /* Repeat */
				DHtreeitem.NameItem = S_str;
				DHtreeitem.Line = i;
				InfoTreeView.push_back(DHtreeitem);
			}

			sc = sscanf_s(iText,"	dialog	%[^,']",str,300);
			if(sc!=-1 && sc!=0)
			{
				string iSea = iText;
				if(iSea.find("dialogitem") == -1) {
					AddItemTreeView(iHTR[7], (LPSTR)str); /* Dialog */
					DHtreeitem.NameItem = str;
					DHtreeitem.Line = i;
					InfoTreeView.push_back(DHtreeitem);
				}
			}

			sc = S_str.find("="); 
			if(sc!=-1)
			{	
				for(int iT = 0; iT < S_str.size(); iT++)
				{
					if(S_str[iT] == 32 || S_str[iT] == 9)
					{
						S_str.erase(iT,1);
						iT--;
					}
				}
				if(S_str.find("'") == -1 && S_str.find(";") == -1 && S_str.find(".") == -1)
				{
					AddItemTreeView(iHTR[9], (LPSTR)S_str.c_str()); /* Const */	
					DHtreeitem.NameItem = S_str;
					DHtreeitem.Line = i;
					InfoTreeView.push_back(DHtreeitem);
				}
			}

			sc = sscanf_s(iText,"	virtual at %s",str,300);
			if(sc!=-1 && sc!=0) {
				string iSea = "virtual at ";
				iSea += str;
				AddItemTreeView(iHTR[3], (LPSTR)iSea.c_str()); /* Virtual */
				DHtreeitem.NameItem = iSea;
				DHtreeitem.Line = i;
				InfoTreeView.push_back(DHtreeitem);
			}

			sc = sscanf_s(iText,"	import %[^,\]",str,300);
			if(sc!=-1 && sc!=0)
			{
				string iSea = "import ";
				iSea += str;
				AddItemTreeView(iHTR[5], (LPSTR)iSea.c_str()); /* Import */
				DHtreeitem.NameItem = iSea;
				DHtreeitem.Line = i;
				InfoTreeView.push_back(DHtreeitem);
			}

			sc = sscanf_s(iText,"	 macro %s",str,300);
			if(sc!=-1 && sc!=0)
			{
				AddItemTreeView(iHTR[8], str); /* Macro */
				DHtreeitem.NameItem = str;
				DHtreeitem.Line = i;
				InfoTreeView.push_back(DHtreeitem);
			}
			ZeroMemory(iText,iTextLength);
		}
	}
	delete[] iText;
	TreeView_Expand(TreeView_R->hWnd,NameASM,TVM_EXPAND);
	TreeView_SetTextColor(TreeView_R->hWnd,RGB(71,60,139));
	TreeView_SetLineColor(TreeView_R->hWnd,RGB(71,60,139));

	/* Если родительский элемент остался без дочерних, удаляем его */
	for(int i = 0; i < 10; i++)
	{
		HTREEITEM itemTR = TreeView_GetChild(TreeView_R->hWnd,iHTR[i]);
		if(itemTR == 0) TreeView_DeleteItem(TreeView_R->hWnd,iHTR[i]);

		ZeroMemory(&iItem,sizeof(TVITEM));
		iItem.mask = TVIF_TEXT;
		char etr[100]={0};
		iItem.pszText=etr;
		iItem.cchTextMax=100;
		iItem.hItem = iHTR[i];
		TreeView_GetItem(TreeView_R->hWnd,&iItem);
		string fName = iItem.pszText;
		for(int kk = 0; kk < Name_Labels.size(); kk++)
		{
			if(Name_Labels[kk].iName == fName) TreeView_Expand(TreeView_R->hWnd,iHTR[i],TVM_EXPAND);
		}
	}
}

/* Добавление нового элемента к  {"Proc","Labels","Struct","Virtual","Repeat","Import","Include",
																		"Dialog","Macro","Const"}*/
void AddItemTreeView(HTREEITEM hItem, LPSTR Src)
{
	ZeroMemory(&iItem,sizeof(TVITEM));
	ZeroMemory(&isItem,sizeof(TV_INSERTSTRUCT));
	iItem.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	iItem.iImage = 2;
	iItem.iSelectedImage = 2;
	isItem.hInsertAfter = TVI_FIRST;
	iItem.pszText = (LPSTR)Src;
	insItem.hParent = hItem;
	insItem.item = iItem;
	TreeView_InsertItem(TreeView_R->hWnd,&insItem);
}

/* Всё существующие включения */
void AllIncludes()
{
	int iIS = 0;
	int iS = -1;
	ExpState.clear();
	NameSelInclude.clear();
	ZeroMemory(&itemEx,sizeof(itemEx));
	itemEx.mask = TVIS_EXPANDED;
	if(iInclude == 1) {
		State = TreeView_GetItemState(AllInc_TrV->hWnd,Include,&itemEx);
		if(State == 98 || State == 96) iIS = 1;
		ExpState.push_back(Include);
		for(int iCount = 0; iCount < htreeitem.size(); iCount++)
		{
			State = TreeView_GetItemState(AllInc_TrV->hWnd,htreeitem[iCount],&itemEx);
			if(State == 96 || State == 98)
			{
				ExpState.push_back(htreeitem[iCount]);
			}
		}
		for(int iCount = 0; iCount < ExpState.size(); iCount++)
		{
			ZeroMemory(&itemEx,sizeof(itemEx));
			itemEx.mask = TVIF_TEXT;
			char etr[100]={0};
			itemEx.pszText=etr;
			itemEx.cchTextMax=100;
			itemEx.hItem = ExpState[iCount];
			TreeView_GetItem(AllInc_TrV->hWnd,&itemEx);
			NameSelInclude.push_back(itemEx.pszText);
		}
	}
		
	TreeView_DeleteAllItems(AllInc_TrV->hWnd);
		
		string Search_Word;
		char pth[150] = {0};
					GetModuleFileName(NULL,pth,150); /* Получаем полный путь к исполняемому файлу, т.к. в той же папке лежит компилятор.
																		А для запуска самого компилятора нужен полный путь к нему */
					path_to_the_include = pth; /* Полученный путь заносим в string, что бы проще было получить только путь, без .exe */
					int pst = path_to_the_include.rfind("\\");
					path_to_the_include.erase(pst + 1,path_to_the_include.length());
					path_to_the_include += "INCLUDE\\";
					OriginalDirectory = path_to_the_include;
					if(Directory.size() != 0) path_to_the_include = Directory; // Если потребуется поиск во вложенных папках					
					Search_Word = "*.*";
					lstrcpy(pth,Search_Word.c_str());

			/* Загрузка массива изображений для TreeView */
			HMODULE hMod = GetModuleHandle(NULL);
			HIMAGELIST himl2 = ImageList_Create(16,16,ILC_COLOR16,2,4);
			HBITMAP TrV = LoadBitmap(hMod,MAKEINTRESOURCE(IDB_BITMAP36)); 
			ImageList_Add(himl2,TrV,NULL);
			DeleteObject(TrV); 
			TrV = LoadBitmap(hMod,MAKEINTRESOURCE(IDB_BITMAP37)); 
			ImageList_Add(himl2,TrV,NULL);
			DeleteObject(TrV);
			TrV = LoadBitmap(hMod,MAKEINTRESOURCE(IDB_BITMAP38)); 
			ImageList_Add(himl2,TrV,NULL);
			DeleteObject(TrV);
			TreeView_SetImageList(AllInc_TrV->hWnd,himl2,TVSIL_NORMAL);

		tvitem.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM | TVIF_CHILDREN;
		tvitem.pszText = "INCLUDE";
		tvitem.cChildren = 1;
		tvitem.iImage = 0;
		tvitem.iSelectedImage = 0;
		insItem.hParent = NULL;
		insItem.hInsertAfter = TVI_ROOT;
		insItem.item = tvitem;
		Include = TreeView_InsertItem(AllInc_TrV->hWnd,&insItem); /* Вставка элемента в TreeView */
		iInclude = 1;

		htreeitem.clear();

		FindFilesInclude(path_to_the_include.c_str(),"*.*", Include); // Первый поиск (цель - все файлы в папке Include) 
	

		/* Вставка элемента в TreeView */
		TreeView_SetTextColor(AllInc_TrV->hWnd,RGB(71,60,139));
		TreeView_SetLineColor(AllInc_TrV->hWnd,RGB(71,60,139));
		//TreeView_Expand(AllInc_TrV->hWnd,Include,TVM_EXPAND);

		for(int iCount = 0; iCount < htreeitem.size(); iCount++)
		{
			itemEx.mask = TVIF_TEXT;
			char etr[100]={0};
			itemEx.pszText=etr;
			itemEx.cchTextMax=100;
			itemEx.hItem = htreeitem[iCount];
			TreeView_GetItem(AllInc_TrV->hWnd,&itemEx);
			for(int rCount = 0; rCount < NameSelInclude.size(); rCount++)
			{
				if(itemEx.pszText == NameSelInclude[rCount])
				{
					TreeView_Expand(AllInc_TrV->hWnd,htreeitem[iCount],TVM_EXPAND);
					iS = 1;
				}
			}
		}
		if(iIS == 1) TreeView_Expand(AllInc_TrV->hWnd,Include,TVM_EXPAND);
}

/* Функция создаёт новую переменную окружения для включений*/
void SetInvVar() 
{
	char buffEnVar[12000] = {0};
	string EnvironmentVariable;
	string Path_INCLUDE;
	GetEnvironmentVariable("include",buffEnVar,12000);
	EnvironmentVariable = buffEnVar;
	GetModuleFileName(NULL,buffEnVar,12000);
	Path_INCLUDE = buffEnVar;
	int posFASM = Path_INCLUDE.rfind("JaeEditor.exe");
	Path_INCLUDE.erase(posFASM,Path_INCLUDE.length());
	Path_INCLUDE += "INCLUDE";
	int posINC = EnvironmentVariable.rfind(Path_INCLUDE);
	if(posINC == -1)
	{
		EnvironmentVariable += Path_INCLUDE;
		SetEnvironmentVariable("include", EnvironmentVariable.c_str());
		GetEnvironmentVariable("include",buffEnVar,12000);
	}
}

/* Функция показывает контекстное меню при нажатие правой кнопкой мыши */
void ShowContextMenu()
{
	counter = TabCtrl_GetCurSel(TabControl->hWnd);
	POINT PosCur_HEdit,PosCur_Tab,PosCur_TabControl;
	RECT rcedit, rctabcontrol, PointTabControl, rctabcontrol_2;
	GetCursorPos (&PosCur_HEdit);
	GetCursorPos (&PosCur_Tab);
	GetCursorPos (&PosCur_TabControl);
	int rcX = PosCur_HEdit.x;
	int rcY = PosCur_HEdit.y;
	ScreenToClient (TabNumber[counter].hwndScintilla, &PosCur_HEdit);
	GetClientRect(TabNumber[counter].hwndScintilla,&rcedit);
	ScreenToClient (TabControl->hWnd, &PosCur_Tab);
	TabCtrl_GetItemRect(TabControl->hWnd,counter,&rctabcontrol);
	ScreenToClient (TabControl->hWnd, &PosCur_TabControl);
	int ct = TabCtrl_GetItemCount(TabControl->hWnd);
	TabCtrl_GetItemRect(TabControl->hWnd,ct,&rctabcontrol_2);
	GetClientRect(TabControl->hWnd, &PointTabControl);

	if((PosCur_Tab.x > rctabcontrol.left 
		&& PosCur_Tab.x < rctabcontrol.right) 
		&& (PosCur_Tab.y > rctabcontrol.top 
		&& PosCur_Tab.y < rctabcontrol.bottom)) 
	{
		TrackPopupMenu(ParentWindow->hEmptyTabMenu, TPM_LEFTALIGN | TPM_RIGHTBUTTON,rcX,rcY,NULL, ParentWindow->hWnd, NULL);
	} 
	else if((PosCur_TabControl.x > rctabcontrol.right 
			&& PosCur_TabControl.x < PointTabControl.right) 
			&& (PosCur_TabControl.y > rctabcontrol.top 
			&& PosCur_TabControl.y < rctabcontrol.bottom)) 
	{
		TrackPopupMenu(ParentWindow->hTabMenu, TPM_LEFTALIGN | TPM_RIGHTBUTTON,rcX,rcY,NULL, ParentWindow->hWnd, NULL);
	}
}

/* Функция вывода в StatusBar данных */
void InStatusBar() 
{
	counter = TabCtrl_GetCurSel(TabControl->hWnd);
	int statwidths[] = {300,550, -1};
	SendMessage(StatusBar->hWnd, SB_SETPARTS, sizeof(statwidths)/sizeof(int), (LPARAM)statwidths);
	SendMessage(StatusBar->hWnd, SB_SETTEXT, 0,((LPARAM)"  "));
	SendMessage(StatusBar->hWnd, SB_SETTEXT, 1,((LPARAM)"  "));
	SendEditor(EM_GETSEL, 0,(LPARAM)&pt);
	int Rt_1 = SendEditor(EM_LINEFROMCHAR, (-1), 0); //Ln
	int Rt_2 = pt.x - SendEditor(EM_LINEINDEX, (-1) ,0); //Col
	Rt_1++;Rt_2++;
	itoa(Rt_1,buff,10);
	char bstr[100] = " Ln: ";
	lstrcat(bstr,buff);

	if(Rt_2>0) 
	{
		itoa(Rt_2,buff,10);
		lstrcat(bstr,"  Col: ");
		lstrcat(bstr,buff);
		SendMessage(StatusBar->hWnd, SB_SETTEXT, 2 ,((LPARAM)bstr));
		strcpy(StrColArray,bstr);
	} 
	else 
	{
		SendMessage(StatusBar->hWnd, SB_SETTEXT, 2,((LPARAM)StrColArray));
	}
}

/* Обработчик событий */
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
NMHDR* nmhdr = (LPNMHDR) lParam;
NMTVGETINFOTIP* nmInfTip = (LPNMTVGETINFOTIP) lParam;
SELCHANGE *selchange = (SELCHANGE*) lParam;
ENDROPFILES *dropfiles = (ENDROPFILES *) lParam;
LPMINMAXINFO lpmmi = (LPMINMAXINFO) lParam; /* информацию о развернутом размере окна и устанавливаемых позициях
																		ее минимального и максимального размера */
SCNotification *pMsg = (SCNotification*)lParam;
PAINTSTRUCT  ps;
POINT lPoint;
LPNMMOUSE lpnm = (LPNMMOUSE) lParam; /* Сообщения от тулбара */

    /* Если произошло нажатие на иконку в трее */
	if(message == MYWM_NOTIFYICON && lParam == WM_LBUTTONDOWN)
	{
		if (iTray==0)
		{
			ShowWindow(ParentWindow->hWnd,SW_HIDE); // скрыть окно при нажатии на иконку;
			iTray=1;
		} 
		else
		{
			ShowWindow(ParentWindow->hWnd,SW_SHOW); // показать окно при нажатии на иконку;
			iTray=0;
		}
	}	

switch (message)
{
	case WM_DROPFILES: /* Перетаскивание файлов */
	{
		char lpszFile[MAX_PATH] = {0};
		int uFile;
		HDROP hDrop = (HDROP)wParam;;
		uFile = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, NULL);	
			for(int u_ = 0; u_ < uFile; u_++) {
				DragQueryFile(hDrop, u_, lpszFile, MAX_PATH);
				OpeningFile(lpszFile);
				lpszFile[0] = '\0';
			}
		DragFinish(hDrop);
		break;
	}
	case WM_DRAWITEM: /* Перерисовка надписи на шапке таба */
	{
		LPDRAWITEMSTRUCT lpdis;
		lpdis = (LPDRAWITEMSTRUCT)lParam;
		int CItem = TabCtrl_GetItemCount(TabControl->hWnd);
		counter = TabCtrl_GetCurSel(TabControl->hWnd);

		if(TabControl->hWnd == lpdis->hwndItem && counter == lpdis->itemID)
		{
			if(TabNumber[lpdis->itemID].BufferName.length() == 0)
			{
				SetTextColor(lpdis->hDC, RGB(0,104,139));
				TextOut(lpdis->hDC, lpdis->rcItem.left+7, lpdis->rcItem.top+4, "Untitled", 8);
				TabNumber[lpdis->itemID].tabitem.pszText = "Untitled";
			} 
			else
			{
				SetTextColor(lpdis->hDC, RGB(0,104,139));
				TextOut (lpdis->hDC,
						lpdis->rcItem.left+7,
						lpdis->rcItem.top+4,
						(LPCSTR)TabNumber[lpdis->itemID].BufferName.c_str(),
						lstrlen((LPCSTR)TabNumber[lpdis->itemID].BufferName.c_str())
						);
				TabNumber[lpdis->itemID].tabitem.pszText = (LPSTR)TabNumber[lpdis->itemID].BufferName.c_str();
			}				
		} 
		else 
		{
			if(TabNumber[lpdis->itemID].BufferName.length() == 0)
			{
				SetTextColor(lpdis->hDC, RGB(79,148,205));
				TextOut(lpdis->hDC, lpdis->rcItem.left+4, lpdis->rcItem.top+4, "Untitled", 8);
				TabNumber[lpdis->itemID].tabitem.pszText = "Untitled";
			} 
			else 
			{
				SetTextColor(lpdis->hDC, RGB(79,148,205));
				TextOut (lpdis->hDC,
						lpdis->rcItem.left+4,
						lpdis->rcItem.top+4, 
						(LPCSTR)TabNumber[lpdis->itemID].BufferName.c_str(), 
						lstrlen((LPCSTR)TabNumber[lpdis->itemID].BufferName.c_str())
						);
				TabNumber[lpdis->itemID].tabitem.pszText = (LPSTR)TabNumber[lpdis->itemID].BufferName.c_str();
			}	
		}
	break;
	}
	case WM_CREATE:
	{
	return DefWindowProc(hWnd, message, wParam, lParam);
	break;
	}
	case  WM_ENTERSIZEMOVE:
	{
		SendMessage(ParentWindow->hWnd,WM_SETREDRAW,FALSE,NULL);
		break;
	}
	case  WM_EXITSIZEMOVE:
	{
		SendMessage(ParentWindow->hWnd,WM_SETREDRAW,TRUE,NULL);
		SendMessage(ParentWindow->hWnd,WM_SIZE,SIZE_RESTORED,NULL);
		break;
	}
	case WM_NOTIFY:	
	{ 
		counter = TabCtrl_GetCurSel(TabControl->hWnd);
		int count = NULL; 
		if(TabControl_TrV) count = TabCtrl_GetCurSel(TabControl_TrV->hWnd);
		if(nmInfTip->hdr.code == TTN_GETDISPINFO)
		{
			LPTOOLTIPTEXT lpttt = (LPTOOLTIPTEXT)lParam;
			lpttt->hinst = (HINSTANCE)GetWindowLong(ParentWindow->hWnd,GWL_HINSTANCE); 
			switch(lpttt->hdr.idFrom) {
				case 128: lpttt->lpszText = "New (Ctrl+N)"; break;
				case 192: lpttt->lpszText = "Open file (Ctrl+O)"; break;
				case 122: lpttt->lpszText = "Save (Ctrl+S)"; break;
				case 124: lpttt->lpszText = "Save all (Ctrl+Shift+S)"; break;
				case 126: lpttt->lpszText = "Cut (Ctrl+X)"; break;
				case 129: lpttt->lpszText = "Copy (Ctrl+C)"; break;
				case 130: lpttt->lpszText = "Paste (Ctrl+V)"; break;
				case 125: lpttt->lpszText = "Undo (Ctrl+Z)"; break;
				case 183: lpttt->lpszText = "Redo (Ctrl+Y)"; break;
				case 203: lpttt->lpszText = "Compile (Ctrl+F9)"; break;
				case 168: lpttt->lpszText = "Run (F9)"; break;
				case 200: lpttt->lpszText = "Comment out the selected lines (Ctrl+Shift+C)"; break;
				case 201: lpttt->lpszText = "Uncomment the selected lines (Ctrl+Shift+X)"; break;
				case 204: lpttt->lpszText = "Decrease Indent (Ctrl+Shift+Tab)"; break;
				case 205: lpttt->lpszText = "Increase Indent (Shift+Tab)"; break;
				case 208: lpttt->lpszText = "Toggle a bookmark on the current line"; break;
				case 209: lpttt->lpszText = "Move the caret to the previous bookmark"; break;
				case 210: lpttt->lpszText = "Move the caret to the next bookmark"; break;
				case 212: lpttt->lpszText = "Clear all bookmarks in all files"; break;
				case 211: lpttt->lpszText = "Clear all bookmarks in the current file"; break;
				case 234: lpttt->lpszText = "Call autocompletion"; break;
			}
		}
		if(nmInfTip->hdr.code == TTN_GETDISPINFO) /* Всплывающие подсказки для TabControl'ов */
		{
			POINT PosCur, PosCur_Tab;
			RECT rctabcontrol, rc_tab; 
			count = TabCtrl_GetCurSel(TabControl_TrV->hWnd);
			counter = TabCtrl_GetCurSel(TabControl->hWnd);
			GetCursorPos (&PosCur);
			ScreenToClient (TabControl_TrV->hWnd,&PosCur);
			GetCursorPos (&PosCur_Tab);
			ScreenToClient (TabControl->hWnd,&PosCur_Tab);
			TabCtrl_GetItemRect(TabControl_TrV->hWnd,count,&rctabcontrol);
			TabCtrl_GetItemRect(TabControl->hWnd,counter,&rc_tab);

			if((PosCur.x > rctabcontrol.left
				&& PosCur.x < rctabcontrol.right) 
				&& (PosCur.y > rctabcontrol.top 
				&& PosCur.y < rctabcontrol.bottom)) 
			{
				if(count == 0)
				{
					nmInfTip->pszText = "Includes the current page";
				} 
				else if(count == 1)
				{
					nmInfTip->pszText = "All the possible includes";
				} 
				else if(count == 2)
				{
					nmInfTip->pszText = "Code view";
				}
			}
			if((PosCur_Tab.x > rc_tab.left && PosCur_Tab.x < rc_tab.right) 
				&& (PosCur_Tab.y > rc_tab.top && PosCur_Tab.y < rc_tab.bottom))
			{
				if(TabNumber[counter].FileInfo.size() != 0)
				{
					nmInfTip->pszText = (LPSTR)TabNumber[counter].FileInfo.c_str();
				} 
				else
				{
					nmInfTip->pszText = (LPSTR)TabNumber[counter].BufferName.c_str();
				}
			}
			HWND tooltip = TabCtrl_GetToolTips(TabControl_TrV->hWnd);
			HWND tooltip_t = TabCtrl_GetToolTips(TabControl->hWnd);
			SendMessage(tooltip,TTM_SETTIPBKCOLOR,RGB(255,250,250),0);
			SendMessage(tooltip,TTM_SETTIPTEXTCOLOR,RGB(54,54,54),0);
			SendMessage(tooltip_t,TTM_SETTIPBKCOLOR,RGB(255,250,250),0);
			SendMessage(tooltip_t,TTM_SETTIPTEXTCOLOR,RGB(54,54,54),0);
		}
		if(lpnm->hdr.code == NM_CLICK) /* Клик на иконке тулбара */	 
		{
			switch(lpnm->dwItemSpec) 
			{
				case 128: NewTab();						break;
				case 192: FileOpen();					break;
				case 122: FileSave();					break;
				case 124: FileSaveALL(counter);			break;
				case 126: SendEditor(SCI_CUT,0,0);		break;
				case 129: SendEditor(SCI_COPY,0,0);		break;
				case 130: SendEditor(SCI_PASTE,0,0);	break;
				case 125: SendEditor(SCI_UNDO,0,0);		break;
				case 183: SendEditor(SCI_REDO,0,0);		break;
				case 203: Compile(); SetWindowText(TabNumber[counter].Output,csTemp.c_str()); break;
				case 168: 
				{
					Compile();
					ShellExecute(NULL, "open", go_to_the_exe.c_str(), NULL, NULL, SW_SHOWNORMAL);
					SetWindowText(TabNumber[counter].Output,csTemp.c_str());
					break;
				}
				case 200: 
				{
					counter = TabCtrl_GetCurSel(TabControl->hWnd);
					operLines.CommentOutTheSelectedLines(TabNumber[counter].hwndScintilla);
					break;
				}
				case 201: 
				{
					counter = TabCtrl_GetCurSel(TabControl->hWnd);
					operLines.UncommentTheSelectedLines(TabNumber[counter].hwndScintilla);
					break;
				}
				case 204: 
				{
					counter = TabCtrl_GetCurSel(TabControl->hWnd);
					operLines.DecreaseIndent(TabNumber[counter].hwndScintilla);
					break;
				}
				case 205: 
				{
					counter = TabCtrl_GetCurSel(TabControl->hWnd);
					operLines.IncreaseIndent(TabNumber[counter].hwndScintilla);
					break;
				}
				case 208: 
				{
					int line = SendEditor(EM_LINEFROMCHAR, (-1), 0); 
					Toggle_a_bookmark(line); 
					break;
				}
				case 209: Previous_Bookmark(); break;
				case 210: Next_Bookmark(); break;
				case 211: Clear_all_in_the_current_file(); break;
				case 212: Clear_all_in_all_files(); break;
				case 234: 
				{
					int reg = SendEditor(SCI_AUTOCACTIVE, 0, 0);
					if(reg != 0)
					{
						SendEditor(SCI_AUTOCCANCEL, 0, 0);
						Flag_for_the_Autocompletion = 0;
					} 
					else
					{ 
						SendEditor(SCI_AUTOCSHOW, 0, (LPARAM)api2.c_str()); 
						Flag_for_the_Autocompletion = 1; 
					}
					break;
				}		
			}
		}
		if(nmhdr->code == SCN_CHARADDED)
		{
			if(pMsg->ch == ',')
			{
				if(SendEditor(SCI_CALLTIPACTIVE,0,0) == 0)
				{
					char word[1000]; 
					TextRange tr;  
					int pos = SendEditor(SCI_GETCURRENTPOS,0,0);
					int startpos = SendEditor(SCI_WORDSTARTPOSITION,pos-1,false);
					int endpos = SendEditor(SCI_WORDENDPOSITION,pos-1,false);
					tr.chrg.cpMin = startpos; 
					tr.chrg.cpMax = endpos;
					tr.lpstrText = word;
					SendEditor(SCI_GETTEXTRANGE,0, sptr_t(&tr));
					string str = tr.lpstrText;
					str.erase(str.size()-1);
					for(size_t i=0; i<api2_name.size(); i++)
					{
						if(api2_name[i] == str.c_str())
						{  
							pCallTipCurDesc = prototype_api2[i].c_str(); 
							SendEditor(SCI_CALLTIPSHOW,pos,(LPARAM)pCallTipCurDesc);
							const char *pStart = strchr(pCallTipCurDesc,'('); 
							if(pStart != NULL)
							{
								pStart++;
								const char *pEnd = strchr(pStart,',');
								if(pEnd != NULL)
								{
									SendEditor(SCI_CALLTIPSETHLT,pStart-pCallTipCurDesc, pEnd-pCallTipCurDesc); 
									pCallTipNextWord = pEnd+1;
								}
								else
								{
									pEnd = strchr(pStart,')');
									if(pEnd != NULL)
									{
										SendEditor(SCI_CALLTIPSETHLT,pStart-pCallTipCurDesc, pEnd-pCallTipCurDesc); 
										pCallTipNextWord = pEnd+1;
									}
								}
							}
							break;
						}
					}
				} 
				else 
				{
					const char *pStart = pCallTipNextWord;
					if(pStart != NULL) 
					{
						const char *pEnd = strchr(pStart,',');
						if(pEnd == NULL)
						{ 
							pEnd = strchr(pStart,')');
						}
						if(pEnd != NULL)
						{
							SendEditor(SCI_CALLTIPSETHLT,pStart-pCallTipCurDesc, pEnd-pCallTipCurDesc);
							pCallTipNextWord = pEnd+1;
						}
						else 
						{
							SendEditor(SCI_CALLTIPCANCEL,0,0);
						}
					}
				}
			} else if(pMsg->ch == '\n')
			{
				SendEditor(SCI_CALLTIPCANCEL,0,0);
				pCallTipCurDesc = NULL;
				pCallTipNextWord = NULL;    

				/* При нажатии Enter, в начало новой строки вставится столько отступов, сколько их было в предидущей */
				int curPos = SendEditor(SCI_GETCURRENTPOS,0,0);
				int curLine = SendEditor(SCI_LINEFROMPOSITION,curPos,0);
				int lineLength = SendEditor(SCI_LINELENGTH,curLine,0);
					if(curLine > 0 && lineLength <= 2)
					{
						int prevLineLength = SendEditor(SCI_LINELENGTH,curLine - 1,0);
						char* chars = new char[prevLineLength + 1];
							if(chars)
							{
								SendEditor(SCI_GETLINE, curLine - 1, (LPARAM)chars);
								chars[prevLineLength] = 0;
								for(int pos = 0; chars[pos]; pos++)
								{
									if(chars[pos] != ' ' && chars[pos] != '\t')
									{
										chars[pos] = 0; break;
									}
								}
								SendEditor(SCI_REPLACESEL, 0, (LPARAM)chars);
								delete[] chars;
							}
					}
					/* Проверка закладок выставленных и сохранённых в векторе */
					curLine--;
					for(int i = 0; i < TabNumber[counter].break_points.size(); i++)
					{
						if(curLine <= TabNumber[counter].break_points.at(i))
						{
							TabNumber[counter].break_points.at(i) = TabNumber[counter].break_points.at(i) + 1;
						}
					}
			}
			if(pMsg->ch >= 64 && pMsg->ch <= 122)
			{ 
				int pos = SendEditor(SCI_GETCURRENTPOS,0,0);
				if(pos >= 3)
				{
					char word[1000];
					TextRange tr; 
					int pos = SendEditor(SCI_GETCURRENTPOS,0,0);
					int startpos = SendEditor(SCI_WORDSTARTPOSITION,pos-1,false);
					tr.chrg.cpMin = startpos;
					tr.chrg.cpMax = pos;
					tr.lpstrText = word;
					SendEditor(SCI_GETTEXTRANGE,0, sptr_t(&tr));
					string str = tr.lpstrText;

					if(str.size() == 3) 
						SendEditor(SCI_AUTOCSHOW,3,(LPARAM)api2.c_str()); 
					else if(str.size() > 3 && str[str.size()-4] == ' ') 
						SendEditor(SCI_AUTOCSHOW,3,(LPARAM)api2.c_str());  
				}
			}
		}
		if(nmhdr->code == SCN_MARGINCLICK)
		{
			if(pMsg->margin == 1)
			{
				int linenumber = SendEditor(SCI_LINEFROMPOSITION,pMsg->position,0); /* Номер активной строки */
				Toggle_a_bookmark(linenumber);
			} 
			else if(pMsg->margin == 2)
			{
				int linenumber = SendEditor(SCI_LINEFROMPOSITION,pMsg->position,0); /* Номер активной строки */
				int iExpanded = SendEditor(SCI_GETFOLDEXPANDED,linenumber,0);
				SendEditor(SCI_TOGGLEFOLD,linenumber,0);
				Sleep(100); 
				MarkersAdd();
			}
		}
		if(nmhdr->code == SCN_AUTOCSELECTION)
		{
			int pos = SendEditor(SCI_GETCURRENTPOS,0,0);
			int startpos = SendEditor(SCI_WORDSTARTPOSITION,pos-1,false);
			SendEditor(SCI_SETSELECTION,startpos,pos);
			if(Flag_for_the_Autocompletion == 1)  SendEditor(SCI_SETSELECTION,startpos,pos);
			SendEditor(SCI_REPLACESEL,0,(LPARAM)pMsg->text);
			SendEditor(SCI_AUTOCCANCEL,0,0);
			Flag_for_the_Autocompletion = 0;
		}
		if(nmhdr->code == SCN_UPDATEUI && HwndScintilla)
		{
			/* Динамически расширяемая MARGIN_NUMBER с выводом в неё номеров строк */

			char buffer[1024] = {0};
			int number_lines = SendEditor(SCI_GETLINECOUNT,0,0);
			sprintf (buffer, "_%d", number_lines);

			int margin_size = SendEditor(SCI_TEXTWIDTH,STYLE_LINENUMBER,(LPARAM)buffer);
			SendEditor(SCI_SETMARGINWIDTHN, 0, margin_size + 10);

			/* Выставляем маркеры для свёртки текста */
				MarkersAdd();

			InStatusBar(); /* Вывод номера строки и символа в StatusBar */

			/* Подсветка парных скобок (), {}, [], <> */
			long PosBegin = SendEditor(SCI_GETCURRENTPOS, 0, 0);
			long PosEnd = SendEditor(SCI_BRACEMATCH, PosBegin - 1, 0);

			if (PosEnd >= 0)
				SendEditor(SCI_BRACEHIGHLIGHT, PosBegin - 1, PosEnd);
			else
				SendEditor(SCI_BRACEHIGHLIGHT, -1, -1);

			/* Подсветка схожих слов с выделенным, подсвечиваются только целые слова */
			if(pMsg->updated == SC_UPDATE_SELECTION)
			{ 		
				int t_l = SendEditor(WM_GETTEXTLENGTH,0,0);
				t_l++;
				char* seltext = new char[t_l];
				if(seltext)
				{
					ZeroMemory(seltext,t_l);
					int result = SendEditor(SCI_GETSELTEXT,0,(LPARAM)seltext);
					string sel;
					if(result != 0)
					{
						strlwr(seltext);
						sel = seltext;
						if(sel.size() > 2 && sel.size() < 20)
						{
							SendEditor(SCI_SETKEYWORDS,4,(LPARAM)sel.c_str());
							SendEditor(SCI_STYLESETFORE,SCE_ASM_DIRECTIVEOPERAND,RGB(69,139,0));
							SendEditor(SCI_STYLESETBACK,SCE_ASM_DIRECTIVEOPERAND,RGB(202,255,112));
							SendEditor(SCI_STYLESETFONT,SCE_ASM_DIRECTIVEOPERAND,reinterpret_cast<LPARAM>("Courier New")); 
							SendEditor(SCI_STYLESETSIZE,SCE_ASM_DIRECTIVEOPERAND,10);
							SendEditor(SCI_STYLESETBOLD,SCE_ASM_DIRECTIVEOPERAND,SC_WEIGHT_BOLD);
						}
					} 
					else
					{
						SendEditor(SCI_SETKEYWORDS,4,(LPARAM)sel.c_str());
					}
				}
				delete[] seltext;
				SendEditor(SCI_COLOURISE,0,-1);
			}
		}
		/* Фокус на вкладке */
		if(nmhdr->code == NM_CLICK && nmhdr->hwndFrom == TabControl->hWnd) 
		{
			for(int u = 0 ; u < TabNumber.size(); u++) 
			{
				ShowWindow(TabNumber[u].hwndScintilla,SW_HIDE);
				ShowWindow(TabNumber[u].Output,SW_HIDE);
			}
				ShowWindow(AllInc_TrV->hWnd,SW_HIDE);
				ShowWindow(TabNumber[counter].Output,SW_SHOWNOACTIVATE);
				ShowWindow(TabNumber[counter].hwndScintilla,SW_SHOWNOACTIVATE);
					
				Inc_();
				SetFocus(TabNumber[counter].hwndScintilla); // Устанавливает фокус ввода;
		}
		/* Фокус на вкладке */
		if(nmhdr->code == NM_CLICK && nmhdr->hwndFrom == TabControl_TrV->hWnd) 
		{
			Inc_();
		}
		/* Всплывающие подсказки для элементов дерева (включения активной вкладки) */
		if(nmInfTip->hdr.code == TVN_GETINFOTIP) 
		{
			count = TabCtrl_GetCurSel(TabControl_TrV->hWnd);
			if(count == 0)
			{
				TVITEM tv_item;
				HTREEITEM item = nmInfTip->hItem;
				ZeroMemory(&tv_item,sizeof(tv_item));
				tv_item.mask = TVIF_TEXT;
				char etr[100]={0};
				tv_item.pszText=etr;
				tv_item.cchTextMax=100;
				tv_item.hItem = item;
				TreeView_GetItem(TreeView_N->hWnd,&tv_item);
				for(int tv_num = 0; tv_num < InvolvedInclude.size(); tv_num++)
				{
					if(etr == InvolvedInclude[tv_num].NameIncludeWithExten)
					{
						nmInfTip->pszText = (LPSTR)InvolvedInclude[tv_num].PathToTheInclude.c_str();
						break;
					}
				}	
				HWND tooltip = TreeView_GetToolTips(TreeView_N->hWnd);
				SendMessage(tooltip,TTM_SETTIPBKCOLOR,RGB(255,250,250),0);
				SendMessage(tooltip,TTM_SETTIPTEXTCOLOR,RGB(54,54,54),0);
			}
		}
		/* Открытие инклуда по двойному щелчку на нём левой кнопкой мыши */
		if(nmhdr->code == NM_DBLCLK)
		{
			count = TabCtrl_GetCurSel(TabControl_TrV->hWnd);
			if(count == 0)
			{
				TVITEM tv_item;
				HTREEITEM item = TreeView_GetSelection(TreeView_N->hWnd);
				ZeroMemory(&tv_item,sizeof(tv_item));
				tv_item.mask = TVIF_TEXT;
				char etr[100]={0};
				tv_item.pszText=etr;
				tv_item.cchTextMax=100;
				tv_item.hItem = item;
				TreeView_GetItem(TreeView_N->hWnd,&tv_item);
				if(tv_item.hItem != 0)
				{
					for(int tv_num = 0; tv_num < InvolvedInclude.size(); tv_num++)
					{
						if(etr == InvolvedInclude[tv_num].NameIncludeWithExten)
						{
							OpeningFile(InvolvedInclude[tv_num].PathToTheInclude.c_str());
							break;
						}
					}
				}
			} 
			else if(count == 2)
			{
				Goto();
			}
		}
		/* Удаление и добавление инклудов */ 
		if(nmhdr->code == NM_RCLICK && nmhdr->hwndFrom != TabControl_TrV->hWnd && nmhdr->hwndFrom != TabControl->hWnd)
		{
			count = TabCtrl_GetCurSel(TabControl_TrV->hWnd);
			if(count == 1)
			{
				added_to_the_source_code.clear();
				TVITEM tv_item;
				HTREEITEM item = TreeView_GetSelection(AllInc_TrV->hWnd);
				ZeroMemory(&tv_item,sizeof(tv_item));
				tv_item.mask = TVIF_TEXT;
				char etr[100]={0};
				tv_item.pszText=etr;
				tv_item.cchTextMax=100;
				tv_item.hItem = item;
				TreeView_GetItem(AllInc_TrV->hWnd,&tv_item);
				string NameItem = tv_item.pszText;
				if(tv_item.hItem != 0)
				{
					if(NameItem == "INCLUDE")
					{
						POINT pU;
						GetCursorPos(&pU);
						TrackPopupMenu	(ParentWindow->hCodeVeiwIncludesMenu,
										TPM_LEFTALIGN | TPM_RIGHTBUTTON,
										pU.x,
										pU.y,
										NULL,
										ParentWindow->hWnd,
										NULL
										);
					}
					HTREEITEM item_2 = TreeView_GetParent(AllInc_TrV->hWnd,item);
					strlwr(etr);
					string NameSelectedInclude = etr;
					int  i_inc = NameSelectedInclude.find(".inc"); /* Убедимся, что выбран .inc */
					if(i_inc != -1)
					{
						tv_item.hItem = item_2;
						TreeView_GetItem(AllInc_TrV->hWnd,&tv_item);
						strlwr(etr);
						string checkup = etr; /* Переменная для проверки */
						if(checkup == "include")
						{
							added_to_the_source_code = "include \'";
							added_to_the_source_code += NameSelectedInclude;
							added_to_the_source_code += "\'";
						}
						else
						{
							added_to_the_source_code = "include \'";
							added_to_the_source_code += checkup;
							added_to_the_source_code += "\\";
							added_to_the_source_code += NameSelectedInclude;
							added_to_the_source_code += "\'";
						}
						POINT pU;
						GetCursorPos(&pU);
						TrackPopupMenu  (ParentWindow->hTreeViewMenu,
										TPM_LEFTALIGN | TPM_RIGHTBUTTON,
										pU.x,
										pU.y,
										NULL,
										ParentWindow->hWnd,
										NULL
										);
					}
				}
			}
			else if(count == 0)
			{
				del_to_the_source_code.clear();
				TVITEM tv_item;
				HTREEITEM item = TreeView_GetSelection(TreeView_N->hWnd);
				ZeroMemory(&tv_item,sizeof(tv_item));
				tv_item.mask = TVIF_TEXT;
				char etr[100]={0};
				tv_item.pszText=etr;
				tv_item.cchTextMax=100;
				tv_item.hItem = item;
				TreeView_GetItem(TreeView_N->hWnd,&tv_item);
				if(tv_item.hItem != 0)
				{
					string name = etr;
					if(name != "INCLUDE")
					{
						for(int tv_num = 0; tv_num < InvolvedInclude.size(); tv_num++)
						{
							if(etr == InvolvedInclude[tv_num].NameIncludeWithExten) 
							{
								del_to_the_source_code = InvolvedInclude[tv_num].PathToTheInclude;
								i_ = tv_num;
								break;
							}
						}
						int pos_s = del_to_the_source_code.rfind("\\");
						del_to_the_source_code.erase(pos_s,del_to_the_source_code.length());
						pos_s = del_to_the_source_code.rfind("\\");
						del_to_the_source_code.erase(0,pos_s + 1);
						string foldername = del_to_the_source_code;
						del_to_the_source_code = "INCLUDE \'";
						del_to_the_source_code_3 = "INCLUDE \"";
						del_to_the_source_code_5 = "INCLUDE \"";
						del_to_the_source_code_6 = "INCLUDE \'";
						del_to_the_source_code_2 = del_to_the_source_code;
						del_to_the_source_code_4 = del_to_the_source_code_3;
						del_to_the_source_code += foldername;
						del_to_the_source_code_3 += foldername;
						del_to_the_source_code_5 += foldername;
						del_to_the_source_code_6 += foldername;
						del_to_the_source_code += "\\";
						del_to_the_source_code_3 += "\\";
						del_to_the_source_code_5 += "/";
						del_to_the_source_code_6 += "/";
						del_to_the_source_code += name;
						del_to_the_source_code_2 += name;
						del_to_the_source_code_3 += name;
						del_to_the_source_code_4 += name;
						del_to_the_source_code_5 += name;
						del_to_the_source_code_6 += name;
						del_to_the_source_code += "\'"; /* include "folder\*.inc" */
						del_to_the_source_code_2 += "\'"; /* include "*.inc" */
						del_to_the_source_code_3 += "\""; /* include 'folder\*.inc' */
						del_to_the_source_code_4 += "\""; /* include '*.inc' */ 
						del_to_the_source_code_5 += "\"";
						del_to_the_source_code_6 += "\'";
						POINT pU;
						GetCursorPos(&pU);
						TrackPopupMenu  (ParentWindow->hCurrentPageIncludesMenu,
										TPM_LEFTALIGN | TPM_RIGHTBUTTON,
										pU.x,
										pU.y,
										NULL,
										ParentWindow->hWnd,
										NULL
										);
					} 
					else 
					{
						POINT pU;
						GetCursorPos(&pU);
						TrackPopupMenu  (ParentWindow->hCodeVeiwIncludesMenu,
										TPM_LEFTALIGN | TPM_RIGHTBUTTON,
										pU.x,
										pU.y,
										NULL,
										ParentWindow->hWnd,
										NULL
										);
					}
				}
			} 
			else if(count == 2) 
			{
				TVITEM tv_item;
				HTREEITEM item = TreeView_GetSelection(TreeView_R->hWnd);
				ZeroMemory(&tv_item,sizeof(tv_item));
				tv_item.mask = TVIF_TEXT;
				char etr[100]={0};
				tv_item.pszText=etr;
				tv_item.cchTextMax=100;
				tv_item.hItem = item;
				TreeView_GetItem(TreeView_R->hWnd,&tv_item);
				string nameitem = tv_item.pszText;
				if(nameitem == "Untitled")
				{
					POINT pU;
					GetCursorPos(&pU);
					TrackPopupMenu( ParentWindow->hCodeVeiwIncludesMenu,
									TPM_LEFTALIGN | TPM_RIGHTBUTTON,
									pU.x,
									pU.y,
									NULL,
									ParentWindow->hWnd,
									NULL
									);
				}
				for(int i = 0; i < TabNumber.size(); i++) 
				{
					if(TabNumber[i].BufferName == nameitem) 
					{
						POINT pU;
						GetCursorPos(&pU);
						TrackPopupMenu( ParentWindow->hCodeVeiwIncludesMenu,
										TPM_LEFTALIGN | TPM_RIGHTBUTTON,
										pU.x,
										pU.y,
										NULL, 
										ParentWindow->hWnd,
										NULL
										);
						break;
					}
				}
				for(int i = 0; i < InfoTreeView.size(); i++) 
				{
					if(InfoTreeView[i].NameItem == nameitem) 
					{
						POINT pU;
						GetCursorPos(&pU);
						TrackPopupMenu( ParentWindow->hAllPossibleIncludesMenu,
										TPM_LEFTALIGN | TPM_RIGHTBUTTON,
										pU.x,
										pU.y,
										NULL,
										ParentWindow->hWnd,
										NULL
										);
						break;
					}
				}
			}
		}
	break;
	}
	case WM_GETMINMAXINFO: /* сообщение запрашивающее информацию о размере окна перед его изменением */
	{
		lpmmi->ptMinTrackSize.x = 685; /* минимум ширины окна */
		lpmmi->ptMinTrackSize.y = 458; /* минимум высоты окна */
		break;
	}
	case WM_SIZE: 
	{
		if (iMemControl != 1000)
			break; 
		if (TabControl->hWnd && StatusBar->hWnd) 
		{
			GetClientRect(ParentWindow->hWnd,&rcClient);
			MoveWindow(TabControl->hWnd,rcClient.left+175, rcClient.top+28, rcClient.right-170,rcClient.bottom-47, TRUE);
			MoveWindow(TabControl_TrV->hWnd,rcClient.left,rcClient.top+28,178,rcClient.bottom-48,TRUE);
			GetClientRect(TabControl->hWnd,&rcTabControl);
			GetClientRect(TabControl_TrV->hWnd,&rcTrV);
			MoveWindow(AllInc_TrV->hWnd,rcTrV.left,rcTrV.top,174,rcTrV.bottom-26,TRUE);
			MoveWindow(StatusBar->hWnd, 0,0, rcClient.right, rcClient.bottom, TRUE);
			SendMessage(Toolbar, TB_AUTOSIZE, 0, 0);
			ShowWindow(Toolbar, TRUE);
			for(int u = 0 ; u < TabNumber.size(); u++) 
			{
				if(TabNumber[u].hwndScintilla) 
				{
					MoveWindow( TabNumber[u].hwndScintilla,
								rcTabControl.left + 6,
								rcTabControl.top + 30,
								rcTabControl.right - 10,
								rcTabControl.bottom - 135,
								TRUE
								);
					GetClientRect(TabNumber[u].hwndScintilla, &rcREdit);
				}
				if(TabNumber[u].Output) 
				{
					MoveWindow( TabNumber[u].Output,
								rcTabControl.left + 6,
								rcREdit.bottom + 47,
								rcTabControl.right - 10,
								100,
								TRUE
								);
				}
			}
			if(TreeView_N->hWnd) MoveWindow(TreeView_N->hWnd, rcTrV.left,rcTrV.top,174,rcTrV.bottom-26, TRUE);
			if(TreeView_R->hWnd) MoveWindow(TreeView_R->hWnd, rcTrV.left,rcTrV.top,174,rcTrV.bottom-26, TRUE);
		}
		break;
	}
	case WM_COMMAND:
	{
		ParentWindow->wmId    = LOWORD(wParam); 
		ParentWindow->wmEvent = HIWORD(wParam); 
		switch (ParentWindow->wmId) 
		{
			case ID_OPENFOLDER:
				{
					if(TabNumber[counter].FileInfo.size() != 0)
					{
						string s = "/select, " + TabNumber[counter].FileInfo; 
						ShellExecute(NULL, NULL, "explorer.exe", s.c_str(), NULL, SW_SHOWNORMAL);
					}
					break;
				}
			case ID_CLOSEALLBUTTHIS: CloseAllButThis();			break;
			case ID_CLOSELEFT:		 CloseLeft();				break;
			case ID_CLOSERIGHT:		 CloseRight();				break;
			case ID_MANDEL:			 Add_Project(MANDEL);		break;
			case ID_OPENGL2:		 Add_Project(OPENGL2);		break;
			case ID_PE64DEMO:		 Add_Project(PE64DEMO);		break;
			case ID_TEMPLATE2:		 Add_Project(TEMPLATE2);	break;
			case ID_USECOM2:		 Add_Project(USECOM2);		break;
			case ID_USECOM:			 Add_Project(USECOM);		break;
			case ID_TEMPLATE:		 Add_Project(TEMPLATE);		break;
			case ID_PEDEMO:			 Add_Project(PEDEMO);		break;
			case ID_OPENGL:			 Add_Project(OPENGL);		break;
			case ID_MSCOFF:			 Add_Project(MSCOFF);		break;
			case ID_MINIPAD:		 Add_Project(MINIPAD);		break;
			case ID_DIALOG:			 Add_Project(HelloWorld5);	break;
			case ID_DDRAW:			 Add_Project(HelloWorld4);	break;
			case ID_Hello_World:	 Add_Project(HelloWorld);	break;
			case ID_Hello_World2:	 Add_Project(HelloWorld2);	break;
			case ID_Hello_World3:	 Add_Project(HelloWorld3);	break;
			case ID_DLL:
			{
				counter = TabCtrl_GetCurSel(TabControl->hWnd);
				int gettextlength = GetWindowTextLength(TabNumber[counter].hwndScintilla);
				if(gettextlength == 0) {
					SendEditor(SCI_SETTEXT,0,(LPARAM)DLL); 
					NewTab();
					SendEditor(SCI_SETTEXT,0,(LPARAM)DLL2);
				} 
				else 
				{
					NewTab();
					SendEditor(SCI_SETTEXT,0,(LPARAM)DLL); 
					NewTab();
					SendEditor(SCI_SETTEXT,0,(LPARAM)DLL2);
				}
				break;
			}
			case ID_TOGGLE: 
			{
				int line = SendEditor(EM_LINEFROMCHAR, (-1), 0);
				Toggle_a_bookmark(line);
				break;
			}
			case ID_PREVIOUS: 
			{
				Previous_Bookmark();
				break;
			}
			case ID_NEXT: 
			{
				Next_Bookmark();
				break;
			}
			case ID_UPDATE:				Inc_();								break;
			case ID_GOTO:				Goto();								break;
			case ID_CLEARALL:			Clear_all_in_all_files();			break;
			case ID_CLEARALL_CF:		Clear_all_in_the_current_file();	break;
			case ID_COMMENT:			
			{
				counter = TabCtrl_GetCurSel(TabControl->hWnd);
				operLines.CommentOutTheSelectedLines(TabNumber[counter].hwndScintilla);
				break;
			}
			case ID_UNCOMMENT:			
			{
				counter = TabCtrl_GetCurSel(TabControl->hWnd);
				operLines.UncommentTheSelectedLines(TabNumber[counter].hwndScintilla);
				break;
			}
			case ID_DEC:				
			{
				counter = TabCtrl_GetCurSel(TabControl->hWnd);
				operLines.DecreaseIndent(TabNumber[counter].hwndScintilla);
				break;
			}
			case ID_INC:				
			{
				counter = TabCtrl_GetCurSel(TabControl->hWnd);
				operLines.IncreaseIndent(TabNumber[counter].hwndScintilla);
				break;
			}
			case ID_ADD:				Added_To_The_Source_Code(added_to_the_source_code); break;
			case ID_DEL:				Remove_From_Source_Code(del_to_the_source_code,													
																del_to_the_source_code_2,
																del_to_the_source_code_3,
																del_to_the_source_code_4,
																del_to_the_source_code_5,
																del_to_the_source_code_6,i_); break;
			case ID_CLOSE:				FileClose(wParam);			break;		 /* /File/Close/ */
			case ID_FILE_OPEN:			FileOpen();					break;		 /* /File/Open/ */
			case ID_SAVE:				FileSave();					break;		 /* /File/Save/ */
			case ID_FILE_SAVE_AS:		FileSaveAs();				break;		 /* /File/Save as/ */
			case ID_FILE_SAVE_ALL:		FileSaveALL(counter);		break;		 /* /File/Save all/ */
			case ID_PRINT:				FilePrint();				break;		 /* /File/Print/ */
			case ID_NEW:				NewTab();					break;		 /* /File/New/ */
			case ID_RUN:
			{
				Compile();
				ShellExecute(NULL, "open", go_to_the_exe.c_str(), NULL, NULL, SW_SHOWNORMAL);
				SetWindowText(TabNumber[counter].Output,csTemp.c_str());
				break;
			}
			case ID_COMPILE:
			{
				Compile();
				SetWindowText(TabNumber[counter].Output,csTemp.c_str());
				break;
			}
			case ID_FILEFINDANDREPLASE:
			{
				/* Чтобы обеспечить нормальную работу диалогов, не позволяем открывать два диалого одновременно */
				if(DialogHWND != 0) DestroyWindow(DialogHWND);
				if(DialogHWND_2 != 0) DestroyWindow(DialogHWND_2);
				if(DialogHWND_3 != 0) DestroyWindow(DialogHWND_3);
				DialogHWND_2 = CreateDialog(NULL,MAKEINTRESOURCE(IDD_DIALOG2),ParentWindow->hWnd,MainDlgProc); 
				ShowWindow(DialogHWND_2, SW_SHOWNORMAL);
				break;
			}
			case ID_FILEFIND: 
			{
				/* Чтобы обеспечить нормальную работу диалогов, не позволяем открывать два диалого одновременно */
				if(DialogHWND_2 != 0) DestroyWindow(DialogHWND_2);
				if(DialogHWND != 0) DestroyWindow(DialogHWND);
				if(DialogHWND_3 != 0) DestroyWindow(DialogHWND_3);
				DialogHWND = CreateDialog(NULL,MAKEINTRESOURCE(IDD_DIALOG1),ParentWindow->hWnd,MainDlgProc); 
				ShowWindow(DialogHWND, SW_SHOWNORMAL);
				break;
			}
			case ID_ABOUT:
			{
				/* Чтобы обеспечить нормальную работу диалогов, не позволяем открывать два диалого одновременно */
				if(DialogHWND_2 != 0) DestroyWindow(DialogHWND_2);
				if(DialogHWND_3 != 0) DestroyWindow(DialogHWND_3);
				if(DialogHWND != 0) DestroyWindow(DialogHWND);
				DialogHWND_3 = CreateDialog(NULL,MAKEINTRESOURCE(IDD_DIALOG3),ParentWindow->hWnd,MainDlgProc); 
				ShowWindow(DialogHWND_3, SW_SHOWNORMAL);
				break;
			}
			case ID_UNDO:		SendEditor(SCI_UNDO,0,0);		break;		
			case ID_REDO:		SendEditor(SCI_REDO,0,0);		break;
			case WM_CUT:		SendEditor(SCI_CUT,0,0);		break;
			case WM_COPY:		SendEditor(SCI_COPY,0,0);		break;
			case WM_PASTE:		SendEditor(SCI_PASTE,0,0);		break;
			case WM_CLEAR:		SendEditor(SCI_CLEAR,0,0);		break;
			case EM_SETSEL:		SendEditor(SCI_SETSEL,0,-1);	break;
			case ID_EXIT:		FileCloseAll(wParam);			break;
			default: return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	}
	case WM_CLOSE: FileCloseAll(wParam); break;
}
return DefWindowProc(hWnd, message, wParam, lParam);
}

/* Удаление (include "folder\*.inc" or include "*.inc") из исходного кода */
void Remove_From_Source_Code(string str1, string str2, string str3, string str4, string str5, string str6, int num1) 
{
	counter = TabCtrl_GetCurSel(TabControl->hWnd);
	int TextLength = SendEditor(SCI_GETTEXTLENGTH,0,0);
	TextLength++; 
	char *WindowTex = new char[TextLength];
	SendEditor(SCI_GETTEXT,TextLength,(LPARAM)WindowTex);
	string WinText = WindowTex;
	/* Переводим в верхний регистр строки */
	char etr[100] = {0};
	strcpy(etr,str1.c_str());
	strupr(etr);
	str1 = etr;
	strcpy(etr,str2.c_str());
	strupr(etr);
	str2 = etr;
	strcpy(etr,str3.c_str());
	strupr(etr);
	str3 = etr;
	strcpy(etr,str4.c_str());
	strupr(etr);
	str4 = etr;
	strcpy(etr,str5.c_str());
	strupr(etr);
	str5 = etr;
	strcpy(etr,str6.c_str());
	strupr(etr);
	str6 = etr;
	/*************************************/
	int find_pos = WinText.find(str1);
	if(find_pos != -1) 
	{
		WinText.erase(find_pos,str1.length());
		InvolvedInclude.erase(InvolvedInclude.begin() + num1);
	}

	find_pos = WinText.find(str2);
	if(find_pos != -1) 
	{
		WinText.erase(find_pos,str2.length());
		InvolvedInclude.erase(InvolvedInclude.begin() + num1);
	}

	find_pos = WinText.find(str3);
	if(find_pos != -1) 
	{
		WinText.erase(find_pos,str3.length());
		InvolvedInclude.erase(InvolvedInclude.begin() + num1);
	}

	find_pos = WinText.find(str4);
	if(find_pos != -1) 
	{
		WinText.erase(find_pos,str4.length());
		InvolvedInclude.erase(InvolvedInclude.begin() + num1);
	}

	find_pos = WinText.find(str5);
	if(find_pos != -1) 
	{
		WinText.erase(find_pos,str5.length());
		InvolvedInclude.erase(InvolvedInclude.begin() + num1);
	}

	find_pos = WinText.find(str6);
	if(find_pos != -1) 
	{
		WinText.erase(find_pos,str6.length());
		InvolvedInclude.erase(InvolvedInclude.begin() + num1);
	}
	/* Переводим в нижний регистр строки */
	strcpy(etr,str1.c_str());
	strlwr(etr);
	str1 = etr;
	strcpy(etr,str2.c_str());
	strlwr(etr);
	str2 = etr;
	strcpy(etr,str3.c_str());
	strlwr(etr);
	str3 = etr;
	strcpy(etr,str4.c_str());
	strlwr(etr);
	str4 = etr;
	strcpy(etr,str5.c_str());
	strlwr(etr);
	str5 = etr;
	strcpy(etr,str6.c_str());
	strlwr(etr);
	str6 = etr;
	/*************************************/
	find_pos = WinText.find(str1);
	if(find_pos != -1) 
	{
		WinText.erase(find_pos,str1.length());
		InvolvedInclude.erase(InvolvedInclude.begin() + num1);
	}

	find_pos = WinText.find(str2);
	if(find_pos != -1) 
	{
		WinText.erase(find_pos,str2.length());
		InvolvedInclude.erase(InvolvedInclude.begin() + num1);
	}

	find_pos = WinText.find(str3);
	if(find_pos != -1) 
	{
		WinText.erase(find_pos,str3.length());
		InvolvedInclude.erase(InvolvedInclude.begin() + num1);
	}

	find_pos = WinText.find(str4);
	if(find_pos != -1) 
	{
		WinText.erase(find_pos,str4.length());
		InvolvedInclude.erase(InvolvedInclude.begin() + num1);
	}

	find_pos = WinText.find(str5);
	if(find_pos != -1) 
	{
		WinText.erase(find_pos,str5.length());
		InvolvedInclude.erase(InvolvedInclude.begin() + num1);
	}

	find_pos = WinText.find(str6);
	if(find_pos != -1) 
	{
		WinText.erase(find_pos,str6.length());
		InvolvedInclude.erase(InvolvedInclude.begin() + num1);
	}
	SendEditor(SCI_SETTEXT,0,(LPARAM)WinText.c_str());
	delete []WindowTex;
	UsedIncludes();
}

/* Добавление Include в исходный код (include "folder\*.inc" or include "*.inc") */
void Added_To_The_Source_Code(string Name_Added_Include) 
{
	counter = TabCtrl_GetCurSel(TabControl->hWnd);
	int TextLength = SendEditor(SCI_GETTEXTLENGTH,0,0);
	TextLength++; 
	char *WindowTex = new char[TextLength];
	SendEditor(SCI_GETTEXT,TextLength,(LPARAM)WindowTex);
	Name_Added_Include += "\n";
	Name_Added_Include += WindowTex;
	SendEditor(SCI_SETTEXT,0,(LPARAM)Name_Added_Include.c_str());
	delete []WindowTex;
}

/* Освобождение памяти */
void DelNew() 
{

	TrayMessage(ParentWindow->hWnd, NIM_DELETE, 0, 0, 0); /* Перед закрытием приложения удаляем иконку из трея */

	if (ParentWindow) delete ParentWindow;
	if (TabControl) delete TabControl;
	if (TabControl_TrV) delete TabControl_TrV;
	if (HwndScintilla) delete HwndScintilla;
	if (Output_N) delete Output_N;
	if (TreeView_N) delete TreeView_N;
	if (TreeView_R) delete TreeView_R;
	if (StatusBar) delete StatusBar;

	ReleaseMutex(CProg);
}

/* Компиляция */
void Compile() 
{
	FileSave();

	SECURITY_ATTRIBUTES Sec_Atr; /* Структура безопасности для пайпа */
	ZeroMemory(&Sec_Atr,sizeof(Sec_Atr));
	Sec_Atr.nLength = sizeof(Sec_Atr);
	Sec_Atr.bInheritHandle = TRUE; /* Дескриптор будет унаследован дочерним процессом */
	
	HANDLE han_stdin, han_stdout; /* Дескрипторы пайпа */						
	string	path_to_the_exe, /* В строке будет только путь к файлу, открытому в активной вкладке */
			path_and_name,
			full_path_to_the_exe, /* Полный путь к компилятору с названием и расширением */
			lpOperation;

	char path[150] = {0};
	GetModuleFileName(NULL,path,150); /* Получаем полный путь к исполняемому файлу, в той же папке лежит компилятор.
														Для запуска компилятора нужен полный путь к нему */
	path_to_the_exe = path; /* Полученный путь заносим в string, что бы проще было получить только путь, без .exe */
	path_and_name = TabNumber[counter].FileInfo; 
	int posit = path_to_the_exe.rfind("\\");
	path_to_the_exe.erase(posit + 1,path_to_the_exe.length());
	int pos_point = path_and_name.rfind(".");
	path_and_name.erase(pos_point + 1,path_and_name.length());
	path_and_name += "EXE";
	
	full_path_to_the_exe += path_to_the_exe + "FASM.EXE"; /*  Полный путь к компилятору */

	/* Параметры с которыми будет запущен компилятор */
	lpOperation += "\"" 
				+ full_path_to_the_exe 
				+ "\" \"" 
				+ TabNumber[counter].FileInfo 
				+ "\""; /* Путь к файлу .asm с названием и расширением, и имя файла .exe */

	if(ID_RUN) 
	{
		go_to_the_exe.clear();
		go_to_the_exe += path_and_name; 
	} 
	else 
	{
		go_to_the_exe.clear();
	}
	DeleteFile(go_to_the_exe.c_str());
	CreatePipe(&han_stdin,&han_stdout,&Sec_Atr,0);

	STARTUPINFO sInfo; 
	ZeroMemory(&sInfo,sizeof(sInfo));
	PROCESS_INFORMATION pInfo; 
	ZeroMemory(&pInfo,sizeof(pInfo));
	sInfo.cb=sizeof(sInfo);
	sInfo.dwFlags=STARTF_USESTDHANDLES;
	sInfo.hStdInput=NULL; 
	sInfo.hStdOutput=han_stdout; 
	sInfo.hStdError=han_stdout;
					
	CreateProcess(full_path_to_the_exe.c_str(), 
				 (LPSTR)lpOperation.c_str(), 
				 0, 
				 0, 
				 TRUE, 
				 NORMAL_PRIORITY_CLASS | CREATE_NO_WINDOW, 
				 0, 
				 0, 
				 &sInfo, 
				 &pInfo);

	CloseHandle(han_stdout);
	DWORD reDword; 
	csTemp.erase();
	while(ReadFile(han_stdin,buf_in_out,30000,&reDword,0)) 
	{
		csTemp += buf_in_out;
		ZeroMemory(buf_in_out,reDword+1);
	}
	CloseHandle(pInfo.hProcess);
	CloseHandle(pInfo.hThread);
}

/* Функция помещает иконку приложения в трей */
BOOL TrayMessage (HWND hWnd, DWORD dwMessage, UINT uID, HICON hIcon, PSTR pszTip) 
{ 
	BOOL res; 
	NOTIFYICONDATA ntficon; 
	ntficon.cbSize = sizeof(NOTIFYICONDATA); 
	ntficon.hWnd = hWnd; 
	ntficon.uID = uID; 
	ntficon.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP; 
	ntficon.uCallbackMessage = MYWM_NOTIFYICON;
	ntficon.hIcon = hIcon; 
		if (pszTip) 
		{ 
			ntficon.szTip[64] = (CHAR)(lstrcpyn(ntficon.szTip, "JaeEditor 1.9.15 - it will be useful.", 64));
		} 
		else 
		{ 
			ntficon.szTip[0] = '\0'; 
		} 

		res = Shell_NotifyIcon(dwMessage, &ntficon); 
	return res; 
}

/* Функция вызывает диалог сохранения файла */
void DLGSAVEFILE() 
{
	counter = TabCtrl_GetCurSel(TabControl->hWnd);
	ParentWindow->hFile = CreateFile(ParentWindow->ofn.lpstrFile,
									 GENERIC_WRITE,
									 NULL,
									 (LPSECURITY_ATTRIBUTES)NULL,
									 CREATE_ALWAYS,
									 FILE_ATTRIBUTE_NORMAL,
									 (HANDLE)NULL);

	if(ParentWindow->hFile==NULL) MessageBox(ParentWindow->hWnd,"Can not open file","Error",0x10);

	DWORD nBufLen = NULL;
	nBufLen = (DWORD)SendEditor(SCI_GETTEXTLENGTH,0,0);
	DWORD nBufLenToWrite = NULL;
	nBufLen++;
	char* szWriteBuf = new char[nBufLen];
	ZeroMemory(szWriteBuf,nBufLen);
	if(szWriteBuf) 
	{
		SendEditor(SCI_GETTEXT,(WPARAM)nBufLen,(LPARAM)szWriteBuf);
			if(!WriteFile(ParentWindow->hFile,szWriteBuf,nBufLen,&nBufLenToWrite,NULL)) 
			{
				MessageBox(ParentWindow->hWnd,"Can not read file","Error",0x10);
			}
	}
	delete[] szWriteBuf;
	CloseHandle(ParentWindow->hFile);
}

/* /File/Save/ */
void FileSave() 
{
	counter = TabCtrl_GetCurSel(TabControl->hWnd);
	if(TabNumber[counter].BufferName.length() == 0)
	{
		FileSaveAs();
	}
	else 
	{
		ParentWindow->hFile = CreateFile(TabNumber[counter].FileInfo.c_str(),
										 GENERIC_WRITE,
										 NULL,
										 (LPSECURITY_ATTRIBUTES)NULL,
										 CREATE_ALWAYS,
										 FILE_ATTRIBUTE_NORMAL,
										 (HANDLE)NULL
										 );

		if(ParentWindow->hFile==NULL) MessageBox(ParentWindow->hWnd,"Can not open file","Error",0x10);

		DWORD nBufLen = (DWORD)SendEditor(SCI_GETTEXTLENGTH,0,0);
		DWORD nBufLenToWrite = NULL;
		nBufLen++;
		char* szWriteBuf = new char[nBufLen];
		ZeroMemory(szWriteBuf,nBufLen);

		SendEditor(SCI_GETTEXT,(WPARAM)nBufLen,(LPARAM)szWriteBuf);
		if(!WriteFile(ParentWindow->hFile,szWriteBuf,nBufLen,&nBufLenToWrite,NULL))
			MessageBox(ParentWindow->hWnd,"Can not read file","Error",0x10);
		delete[] szWriteBuf;
		CloseHandle(ParentWindow->hFile);
		TabNumber[counter].tabitem.pszText = (LPSTR)TabNumber[counter].BufferName.c_str();
		TabNumber[counter].tabitem.cchTextMax = lstrlen((LPSTR)TabNumber[counter].BufferName.c_str());
	}
}

/* Поток для обновления дерева */
DWORD WINAPI Thread_for_the_TreeView(LPVOID lpVoid) 
{
	int flag = (int)lpVoid;
	Flag_for_the_TreeView = 1;
	if(flag == 0) 
	{
		UsedIncludes();
	} 
	else if(flag == 1) 
	{
		AllIncludes();
	} 
	else if(flag == 2) 
	{
		CodeView();
	}
	Flag_for_the_TreeView = 0;
	return 0;
}

/* подсветка синтаксиса */
void Syntax_Highlight() {

	SendEditor(SCI_SETMARGINTYPEN, 0, SC_MARGIN_NUMBER);
	SendEditor(SCI_SETMARGINMASKN, 0, SC_MARGIN_NUMBER);
	SendEditor(SCI_SETMARGINWIDTHN, SC_MARGIN_NUMBER, 7);
	SendEditor(SCI_STYLESETFORE, STYLE_LINENUMBER, rvalue.GetRGBValueFromIni("line_number")); /* Цвет LINENUMBERFORE */
	SendEditor(SCI_STYLESETBACK, STYLE_LINENUMBER, rvalue.GetRGBValueFromIni("line_number_background")); /* Цвет LINENUMBERBACK */
	SendEditor(SCI_STYLESETFONT, STYLE_LINENUMBER, reinterpret_cast<LPARAM>("Courier New")); /* Шрифт MARGIN_NUMBER */
	SendEditor(SCI_STYLESETSIZE, STYLE_LINENUMBER, 11); /* Размер шрифта MARGIN_NUMBER */

	/* Параметры текста для выделенных парных скобок */
	SendEditor(SCI_STYLESETFORE,STYLE_BRACELIGHT,RGB(70,130,180));
	SendEditor(SCI_STYLESETBACK,STYLE_BRACELIGHT,RGB(253,245,230)); 
	SendEditor(SCI_STYLESETFONT,STYLE_BRACELIGHT,reinterpret_cast<LPARAM>("Courier New")); 
	SendEditor(SCI_STYLESETBOLD,STYLE_BRACELIGHT,SC_WEIGHT_BOLD);
	SendEditor(SCI_STYLESETSIZE,STYLE_BRACELIGHT,11);

	SendEditor(SCI_CALLTIPSETBACK,RGB(255,240,245),0);
	SendEditor(SCI_CALLTIPSETFORE,RGB(85,26,139),0);
	SendEditor(SCI_CALLTIPSETFOREHLT,RGB(139,34,82),0);

	SendEditor(SCI_SETMARGINTYPEN,1,SC_MARGIN_SYMBOL);
	SendEditor(SCI_SETMARGINMASKN,1,(1<<MARK_BOOKMARK));
	SendEditor(SCI_SETMARGINWIDTHN,1,20);
	SendEditor(SCI_SETMARGINSENSITIVEN,1,TRUE);  /* Чувствительность */
	SendEditor(SCI_SETFOLDMARGINCOLOUR,1,RGB(253,245,230));

	SendEditor(SCI_MARKERDEFINEPIXMAP, MARK_BOOKMARK, (LPARAM)breakpoint_rounded_blue_inverted2_xpm);
	
	SendEditor(SCI_SETCARETLINEVISIBLE,1,1); /* Инициализация CARETLINEVISIBLE */
	SendEditor(SCI_SETCARETLINEBACK,RGB(253,245,230),1); /* Цвет CARETLINEVISIBLE */

	SendEditor(SCI_SETSELFORE,1,RGB(0,104,139)); /* Цвет SELFORE */
	SendEditor(SCI_SETSELBACK,1,RGB(230,230,250)); /* Цвет SELBACK */

	SendEditor(SCI_SETHOTSPOTACTIVEFORE,true,RGB(0,104,139)); /* Цвет ADDITIONALSELFORE */
	SendEditor(SCI_SETHOTSPOTACTIVEBACK,true,RGB(124,252,0)); /* Цвет ADDITIONALSELBACK */

	SendEditor(SCI_SETLEXER, SCLEX_ASM, 0);
	SendEditor(SCI_STYLESETCHARACTERSET,0,SC_CHARSET_RUSSIAN);

	SendEditor(SCI_SETKEYWORDS,0,(LPARAM)asm_operators);
	SendEditor(SCI_STYLESETFORE,SCE_ASM_CPUINSTRUCTION, rvalue.GetRGBValueFromIni("asm_operators"));
	SendEditor(SCI_STYLESETFONT,SCE_ASM_CPUINSTRUCTION,reinterpret_cast<LPARAM>("Courier New")); 
	SendEditor(SCI_STYLESETSIZE,SCE_ASM_CPUINSTRUCTION,10);
	SendEditor(SCI_STYLESETBOLD,SCE_ASM_CPUINSTRUCTION,SC_WEIGHT_BOLD);

	SendEditor(SCI_SETKEYWORDS,1,(LPARAM)asm_registers);
	SendEditor(SCI_STYLESETFORE,SCE_ASM_MATHINSTRUCTION, rvalue.GetRGBValueFromIni("asm_registers"));
	SendEditor(SCI_STYLESETFONT,SCE_ASM_MATHINSTRUCTION,reinterpret_cast<LPARAM>("Courier New"));
	SendEditor(SCI_STYLESETSIZE,SCE_ASM_MATHINSTRUCTION,10); 
	SendEditor(SCI_STYLESETBOLD,SCE_ASM_MATHINSTRUCTION,SC_WEIGHT_BOLD);

	SendEditor(SCI_SETKEYWORDS,2,(LPARAM)asm_mnemonics);
	SendEditor(SCI_STYLESETFORE,SCE_ASM_REGISTER, rvalue.GetRGBValueFromIni("asm_mnemonics"));
	SendEditor(SCI_STYLESETFONT,SCE_ASM_REGISTER,reinterpret_cast<LPARAM>("Courier New"));
	SendEditor(SCI_STYLESETSIZE,SCE_ASM_REGISTER,10); 
	SendEditor(SCI_STYLESETBOLD,SCE_ASM_REGISTER,SC_WEIGHT_BOLD);

	SendEditor(SCI_STYLESETFORE,SCE_ASM_CHARACTER,RGB(205,85,85)); /* \'*/
	SendEditor(SCI_STYLESETFONT,SCE_ASM_CHARACTER,reinterpret_cast<LPARAM>("Courier New")); /* \' - шрифт */
	SendEditor(SCI_STYLESETSIZE,SCE_ASM_CHARACTER,10); /* \' - размер шрифта */
	SendEditor(SCI_STYLESETBOLD,SCE_ASM_CHARACTER,SC_WEIGHT_BOLD);

	SendEditor(SCI_STYLESETFORE,SCE_ASM_IDENTIFIER, rvalue.GetRGBValueFromIni("default_text")); /* Текст по умолчанию */
	SendEditor(SCI_STYLESETFONT,SCE_ASM_IDENTIFIER,reinterpret_cast<LPARAM>("Courier New")); 
	SendEditor(SCI_STYLESETSIZE,SCE_ASM_IDENTIFIER,10); 
	SendEditor(SCI_STYLESETBOLD,SCE_ASM_IDENTIFIER,SC_WEIGHT_BOLD);

	SendEditor(SCI_STYLESETFORE,SCE_ASM_NUMBER, rvalue.GetRGBValueFromIni("numbers")); /* Числа */
	SendEditor(SCI_STYLESETFONT,SCE_ASM_NUMBER,reinterpret_cast<LPARAM>("Courier New")); /* Числа - шрифт */
	SendEditor(SCI_STYLESETSIZE,SCE_ASM_NUMBER,10); /* Числа - размер шрифта */
	SendEditor(SCI_STYLESETBOLD,SCE_ASM_NUMBER,SC_WEIGHT_BOLD);

	SendEditor(SCI_STYLESETFORE,SCE_ASM_COMMENT,RGB(255,140,105)); /* ; */
	SendEditor(SCI_STYLESETFONT,SCE_ASM_COMMENT,reinterpret_cast<LPARAM>("Courier New")); /* ; - шрифт */
	SendEditor(SCI_STYLESETSIZE,SCE_ASM_COMMENT,10); /* ; - размер шрифта */
	SendEditor(SCI_STYLESETBOLD,SCE_ASM_COMMENT,SC_WEIGHT_BOLD);

	SendEditor(SCI_STYLESETFORE,SCE_ASM_OPERATOR,RGB(71,60,139)); /* (){}[]^&*%!# */
	SendEditor(SCI_STYLESETFONT,SCE_ASM_OPERATOR,reinterpret_cast<LPARAM>("Courier New")); /* (){}[]^&*%!# - шрифт */
	SendEditor(SCI_STYLESETSIZE,SCE_ASM_OPERATOR,10); /* (){}[]^&*%!# - размер шрифта */
	SendEditor(SCI_STYLESETBOLD,SCE_ASM_OPERATOR,SC_WEIGHT_BOLD);

	SendEditor(SCI_STYLESETFORE,SCE_ASM_STRING,RGB(205,85,85)); /* \" */
	SendEditor(SCI_STYLESETFONT,SCE_ASM_STRING,reinterpret_cast<LPARAM>("Courier New")); /* \" - шрифт */
	SendEditor(SCI_STYLESETSIZE,SCE_ASM_STRING,10); /* \" - размер шрифта */
	SendEditor(SCI_STYLESETBOLD,SCE_ASM_STRING,SC_WEIGHT_BOLD);

	SendEditor(SCI_STYLESETFORE,SCE_ASM_DEFAULT,RGB(71,60,139)); /* {} */
	SendEditor(SCI_STYLESETFONT,SCE_ASM_DEFAULT,reinterpret_cast<LPARAM>("Courier New")); 
	SendEditor(SCI_STYLESETSIZE,SCE_ASM_DEFAULT,10); 
	SendEditor(SCI_STYLESETBOLD,SCE_ASM_DEFAULT,SC_WEIGHT_BOLD);

	/* Поле для свёртки текста */
    SendEditor(SCI_SETMARGINMASKN,2, SC_MASK_FOLDERS);
    SendEditor(SCI_SETMARGINWIDTHN, 2, 11); 
    SendEditor(SCI_SETMARGINSENSITIVEN, 2, TRUE);
	SendEditor(SCI_SETFOLDMARGINCOLOUR,2, rvalue.GetRGBValueFromIni("fold_margin"));

	SendEditor(SCI_MARKERDEFINEPIXMAP, SC_MARKNUM_FOLDER, (LPARAM)plus_xpm); 
	SendEditor(SCI_MARKERDEFINEPIXMAP, SC_MARKNUM_FOLDEROPEN, (LPARAM)minus_xpm); 
	SendEditor(SCI_MARKERDEFINEPIXMAP, SC_MARKNUM_FOLDEREND, (LPARAM)plus_xpm); 
	SendEditor(SCI_MARKERDEFINEPIXMAP, SC_MARKNUM_FOLDEROPENMID, (LPARAM)minus_xpm);  

	SendEditor(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_TCORNERCURVE); 
	SendEditor(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERSUB, SC_MARK_VLINE); 
	SendEditor(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERTAIL, SC_MARK_LCORNERCURVE);  

    SendEditor(SCI_MARKERSETBACK, SC_MARKNUM_FOLDERSUB, RGB(205,181,205)); 
    SendEditor(SCI_MARKERSETBACK, SC_MARKNUM_FOLDERMIDTAIL, RGB(205,181,205)); 
    SendEditor(SCI_MARKERSETBACK, SC_MARKNUM_FOLDERTAIL, RGB(205,181,205)); 
    
    SendEditor(SCI_SETFOLDFLAGS, 16, 0);

	SendEditor(SCI_COLOURISE,0,-1); /* Перерисовка */
}

/* /File/Save all/ */
void FileSaveALL(int to_rem) 
{
	int c_i = TabCtrl_GetItemCount(TabControl->hWnd);
	for(int CC_i = 0; CC_i < c_i; CC_i++) 
	{
		TabCtrl_SetCurSel(TabControl->hWnd,CC_i);
		FileSave();
	}
	TabCtrl_SetCurSel(TabControl->hWnd,to_rem);
}

/* Функция вызывает диалог открытия файла */
void DLGOPENFILE() 
{
	counter = TabCtrl_GetCurSel(TabControl->hWnd);
	ParentWindow->hFile = CreateFile(ParentWindow->ofn.lpstrFile, 
									 GENERIC_READ,
									 0, 
									 (LPSECURITY_ATTRIBUTES) NULL,
									 OPEN_EXISTING, 
									 FILE_ATTRIBUTE_NORMAL,
									 (HANDLE) NULL);

	if(ParentWindow->hFile==NULL)
		MessageBox(ParentWindow->hWnd,"Can not open file","Error",0x10);

	DWORD nBufLen = NULL;
	nBufLen = GetFileSize(ParentWindow->hFile,NULL);
	DWORD nBufLenToRead = NULL;
	nBufLen++;
	char* szReadBuf = new char[nBufLen];
	ZeroMemory(szReadBuf,nBufLen);
	if(szReadBuf) 
	{
		if(!ReadFile(ParentWindow->hFile,szReadBuf,nBufLen-1,&nBufLenToRead,NULL))
			MessageBox(ParentWindow->hWnd,"Can not read file","Error",0x10);
		SendEditor(SCI_SETTEXT,0,(LPARAM)szReadBuf);
	}
	delete[] szReadBuf;
	CloseHandle(ParentWindow->hFile);
}

/* Функция открывает файл */
void FileOpen() 
{
	counter = TabCtrl_GetCurSel(TabControl->hWnd);
	if (GetOpenFileName(&ParentWindow->ofn)==TRUE) 
	{
		tmp = 1;
		TitleBuf = ParentWindow->ofn.lpstrFile;
		int overlap_ = Overlap(TitleBuf);
		if(overlap_ != 8) 
		{
			if(TabCtrl_GetItemCount(TabControl->hWnd) == 1 
				&& GetWindowTextLength(TabNumber[counter].hwndScintilla) == 0 
				&& tabNum.tabitem.pszText == "Untitled")
			{	
				FileName();
				if(TabNumber[tN].BufferName.length() == 0) 
				{
					TabNumber[tN].tabitem.pszText = "Untitled";
					TabNumber[tN].tabitem.cchTextMax = 8;
				} 
				else 
				{
					TabNumber[tN].tabitem.pszText = (LPSTR)TabNumber[tN].BufferName.c_str();
					TabNumber[tN].tabitem.cchTextMax = lstrlen((LPSTR)TabNumber[tN].BufferName.c_str());
				}
					TabCtrl_SetItem(TabControl->hWnd,counter,&TabNumber[counter].tabitem); // Обновляем вкладку;
					TabCtrl_HighlightItem(TabControl->hWnd,counter,0);
			} 
			else 
			{
					NewTab();	
			}
			TabNumber[counter].FileInfo = ParentWindow->ofn.lpstrFile;
			DLGOPENFILE();

			TitleBuf.clear();
			tmp = NULL;
			ShowWindow(TabNumber[counter].Output,SW_SHOW);
			ShowWindow(TabNumber[counter].hwndScintilla,SW_SHOW);
		} 
		else 
		{
			for(int ol_ = 0; ol_ < TabNumber.size(); ol_++) 
			{
				if(TabNumber[ol_].FileInfo == ParentWindow->ofn.lpstrFile) 
				{
					TabCtrl_SetCurSel(TabControl->hWnd,ol_);
					ShowWindow(TabNumber[counter].Output,SW_SHOW);
					ShowWindow(TabNumber[counter].hwndScintilla,SW_SHOW);
				}
			}
		}
		Inc_();
	}
}

/* Открывает файл, принимает путь к файлу*/
void OpeningFile(string File_Path) 
{
	counter = TabCtrl_GetCurSel(TabControl->hWnd);
	tmp = 1;
	TitleBuf = File_Path; /* Получаем имя файла с расширением */
	int overlap_ = Overlap(TitleBuf);
	if(overlap_ != 8) 
	{
		ParentWindow->hFile = CreateFile(File_Path.c_str(), 
										 GENERIC_READ,
										 0, 
										 (LPSECURITY_ATTRIBUTES) NULL,
										 OPEN_EXISTING, 
										 FILE_ATTRIBUTE_NORMAL,
										 (HANDLE)NULL
										);

		if(ParentWindow->hFile==NULL) MessageBox(ParentWindow->hWnd, File_Path.c_str(), "Can not open file", 0x10);

		DWORD nBufLen = NULL;
		nBufLen = GetFileSize(ParentWindow->hFile,NULL);
		DWORD nBufLenToRead = NULL;
		nBufLen++;
		char* szReadBuf = new char[nBufLen];
		ZeroMemory(szReadBuf,nBufLen);

		if(szReadBuf) 
		{
			if(!ReadFile(ParentWindow->hFile,szReadBuf,nBufLen-1,&nBufLenToRead,NULL))
			{
				MessageBox(ParentWindow->hWnd, File_Path.c_str(), "Can not read file ", 0x10);
			}
			else
			{
				if(TabCtrl_GetItemCount(TabControl->hWnd) == 1 
					&& GetWindowTextLength(TabNumber[counter].hwndScintilla) == 0 
					&& tabNum.tabitem.pszText == "Untitled") 
				{
					FileName();
					if(TabNumber[tN].BufferName.length() == 0) 
					{
						TabNumber[tN].tabitem.pszText = "Untitled";
						TabNumber[tN].tabitem.cchTextMax = 8;
					} 
					else 
					{
						TabNumber[tN].tabitem.pszText = (LPSTR)TabNumber[tN].BufferName.c_str();
						TabNumber[tN].tabitem.cchTextMax = lstrlen((LPSTR)TabNumber[tN].BufferName.c_str());
					}
					TabCtrl_SetItem(TabControl->hWnd,counter,&TabNumber[counter].tabitem); // Обновляем вкладку;
					TabCtrl_HighlightItem(TabControl->hWnd,counter,0);
				} 
				else
				{
					NewTab();
				} 

				TabNumber[counter].FileInfo = File_Path;


				SendEditor(SCI_SETTEXT,0,(LPARAM)szReadBuf);
			}
		}

		delete[] szReadBuf;
			
		CloseHandle(ParentWindow->hFile);	

		TitleBuf.clear();
		tmp = NULL;
	} 
	else 
	{
		for(int ol_ = 0; ol_ < TabNumber.size(); ol_++) 
		{
			if(TabNumber[ol_].FileInfo == File_Path) 
			{
				TabCtrl_SetCurSel(TabControl->hWnd,ol_);
				ShowWindow(TabNumber[counter].Output,SW_SHOWNOACTIVATE);
				ShowWindow(TabNumber[counter].hwndScintilla,SW_SHOWNOACTIVATE);
			}
		}
	}
	Inc_();
	for(int u = 0 ; u < TabNumber.size(); u++) 
	{
		ShowWindow(TabNumber[u].hwndScintilla,SW_HIDE);
	}
	ShowWindow(TabNumber[counter].hwndScintilla,SW_SHOWNOACTIVATE);
	SetFocus(TabNumber[counter].hwndScintilla);
} 

/*Функция удаляет активную вкладку и её содержимое.
В том чесле удаляется элемент вектора соответствующий
номеру удалённой вкладки. Фокус переводится на вкладку
с индексом [0].*/
void CloseTab() 
{
	counter = TabCtrl_GetCurSel(TabControl->hWnd);
	/* Удаляем содержимое активной вкладки */
	DestroyWindow(TabNumber[counter].hwndScintilla);
	DestroyWindow(TabNumber[counter].Output);
	/* Удаляем вкладку */
	TabCtrl_DeleteItem(TabControl->hWnd,counter);
	/* Удаляем элемент вектора соответсвующий номеру удалённой вкладки */
	TabNumber.erase(TabNumber.begin()+counter);
	/*Поскольку после удаления элементов в конце вектора остаётся занята память,
	которую они занимали, проделывается такой фокус: создаётся временная копия 
	вектора TabNumber, в которую копируются все оставшиеся элементы TabNumber, 
	причём памяти эта копия отъедает ровно на counter элементов, после чего новый
	кусочек памяти передаётся во владение самому TabNumber, а старый кусочек - времянке.
	Времянка тут же уничтожается, а в векторе TabNumber не отъедается неиспользованная память.
	Разумеется, это имеет смысл лишь в том случае, если мы не собираемся расширять TabNumber
	в дальнейшем.*/
	vector<tabcounter>(TabNumber).swap(TabNumber);

	/* Устанавливаем фокус на вкладку с индексом [0] и показываем содержимое вкладки */
	TabCtrl_SetCurSel(TabControl->hWnd,0);
	counter = TabCtrl_GetCurSel(TabControl->hWnd);
	//TabNumber[counter].tabitem.pszText = (LPSTR)TabNumber[counter].BufferName.c_str();
	ShowWindow(TabNumber[counter].hwndScintilla,SW_SHOW);
	ShowWindow(TabNumber[counter].Output,SW_SHOW);
	int count = TabCtrl_GetCurSel(TabControl_TrV->hWnd);
	if(Flag_for_the_TreeView != 1) CreateThread(0,0,Thread_for_the_TreeView,(LPVOID)count,0,0); /* Потока обновления дерева */
	if(count == 0) 
	{
		ShowWindow(TreeView_N->hWnd,SW_SHOW);
	} 
	else if(count == 1) 
	{
		ShowWindow(AllInc_TrV->hWnd,SW_SHOW);
	} 
	else if(count == 2) 
	{
		ShowWindow(TreeView_R->hWnd,SW_SHOW);
	}
	tN--; /* Cокращаем нумерацию вкладок в структуре TC_ITEM */
}

/* Функция создаёт новую вкладку, переводит на неё фокус 
и показывает содержимое этой вкладки */
void NewTab() 
{
	/* Освобождаем часть мамяти */
	if (HwndScintilla) delete HwndScintilla;
	if (Output_N) delete Output_N;
	
	tN++; /* Инкремент счётчика вкладок */	

	/* Добавляем вкладку в TabConrol */
	TabCtrl_InsertItem(TabControl->hWnd,tN,&tabNum.tabitem);
		
	HwndScintilla = new Wnd(0,
							"Scintilla",
							"",
							WS_CHILD | WS_VISIBLE| WS_CLIPCHILDREN,
							rcTabControl.left + 6,
							rcTabControl.top + 30,
							rcTabControl.right - 10,
							rcTabControl.bottom - 135,
							TabControl->hWnd,
							NULL,
							NULL
							);

	tabNum.hwndScintilla = HwndScintilla->hWnd;

	Output_N = new Wnd( WS_EX_ACCEPTFILES,
						"RICHEDIT",
						NULL,
						WS_CHILD | WS_VISIBLE | ES_DISABLENOSCROLL |  WS_VSCROLL | 
						ES_READONLY | ES_LEFT | ES_MULTILINE  | ES_AUTOVSCROLL,
						rcTabControl.left + 6,
						rcREdit.bottom + 47,
						rcTabControl.right - 10,
						100,
						TabControl->hWnd,
						NULL,
						NULL
						);

	tabNum.Output = Output_N->hWnd;	

		CHARFORMAT CharF;
		ZeroMemory(&CharF, sizeof(CharF));
		CharF.cbSize = sizeof(CHARFORMAT);
		CharF.dwMask = CFM_SIZE | CFM_FACE | CFM_COLOR | CFM_CHARSET;
		CharF.crTextColor = RGB(72,61,139);
		CharF.bPitchAndFamily = FW_THIN;
		lstrcpy(CharF.szFaceName , "Courier New");
		SendMessage(Output_N->hWnd,EM_SETCHARFORMAT,0,(LPARAM)&CharF);
																			
	TabNumber.push_back(tabNum); 
	/* Скрываем содержимое предыдущей вкладки */
	counter = TabCtrl_GetCurSel(TabControl->hWnd);
	ShowWindow(TabNumber[tN-1].Output,SW_HIDE);
	ShowWindow(TabNumber[tN-1].hwndScintilla,SW_HIDE);

	TabCtrl_SetCurSel(TabControl->hWnd,tN);
	/* Показываем содержимое созданной вкладки */
	ShowWindow(TabNumber[tN].Output,SW_SHOWNOACTIVATE);
	ShowWindow(TabNumber[tN].hwndScintilla,SW_SHOWNOACTIVATE);

	Syntax_Highlight();

	/* Задаём имя на шапке таба */
	FileName();
	if(TabNumber[tN].BufferName.length() == 0) 
	{
		TabNumber[tN].tabitem.pszText = "Untitled";
		TabNumber[tN].tabitem.cchTextMax = 8;
	} 
	else 
	{
		TabNumber[tN].tabitem.pszText = (LPSTR)TabNumber[tN].BufferName.c_str();
		TabNumber[tN].tabitem.cchTextMax = lstrlen((LPSTR)TabNumber[tN].BufferName.c_str());
	}

	TabCtrl_SetItem(TabControl->hWnd,tN,&TabNumber[tN].tabitem); /* Обновляем вкладку */
	TabCtrl_HighlightItem(TabControl->hWnd,tN,0);

	int count = TabCtrl_GetCurSel(TabControl_TrV->hWnd);
	if(count == 0) 
	{
		ShowWindow(TreeView_N->hWnd,SW_SHOW);
	} 
	else if(count == 1) 
	{
		ShowWindow(AllInc_TrV->hWnd,SW_SHOW);
	} 
	else if(count == 2) 
	{
		ShowWindow(TreeView_R->hWnd,SW_SHOW);
	}
	tmp = 0;
	Inc_();
}

/* Функция получает имя файла с его расширением из пути к файлу */
void FileName() 
{
	counter = TabCtrl_GetCurSel(TabControl->hWnd);
	int position = TitleBuf.rfind("\\");
	TabNumber[counter].BufferName = TitleBuf.substr(position+1,TitleBuf.length()-position);
}

/* Функция отправляет открытый файл на печать, на принтер по умолчанию */
int PrintFileToPrinter(char* sFileName) 
{
	int ret = 0;
	HANDLE hPrinter;
	DOC_INFO_1 DocInfo; // структуру документа, который будет напечатан
	DWORD dwJob;
	DWORD dwBytesWritten;
	char buffer[4096];
	DWORD dwCount;
	FILE* pF;

	TCHAR sPrinterName[MAX_PATH] = {0};
	DWORD Size = MAX_PATH;

	GetDefaultPrinter(sPrinterName, &Size);

	pF = fopen(sFileName, "rb");
	if (pF) 
	{
		if(OpenPrinter( sPrinterName, &hPrinter, NULL )) 
		{
			DocInfo.pDocName = sFileName;
			DocInfo.pOutputFile = NULL;
			DocInfo.pDatatype = "TEXT";
			if( (dwJob = StartDocPrinter( hPrinter, 1, (LPBYTE)&DocInfo )) != 0 ) 
			{
				if(StartPagePrinter(hPrinter)) 
				{
					while(ret = !feof(pF)) 
					{
						dwCount = fread(buffer,sizeof(char),sizeof(buffer)/sizeof(char),pF);
						if (dwCount <= 0) break;
						if( !WritePrinter( hPrinter, &buffer[0] , dwCount, &dwBytesWritten ) ) break;
					}
					EndPagePrinter( hPrinter );
				}
				EndDocPrinter( hPrinter );
			}
			ClosePrinter( hPrinter );
		}
		fclose(pF);
	}
	return ret;
}

/* /File/Print/ */
void FilePrint() 
{
	counter = TabCtrl_GetCurSel(TabControl->hWnd);
	if(TabNumber[counter].BufferName.length()==0) 
	{
		GetSaveFileName(&ParentWindow->ofn);
		if((strlen(ParentWindow->ofn.lpstrFile) != 0))
		{
			DLGSAVEFILE();
			TitleBuf = ParentWindow->ofn.lpstrFile;
			TabNumber[counter].FileInfo = ParentWindow->ofn.lpstrFile;
			FileName();
				if(TabNumber[counter].BufferName.length() == 0) 
				{
					TabNumber[counter].tabitem.pszText = "Untitled";
					TabNumber[counter].tabitem.cchTextMax = 8;
				} 
				else 
				{
					TabNumber[counter].tabitem.pszText = (LPSTR)TabNumber[tN].BufferName.c_str();
					TabNumber[counter].tabitem.cchTextMax = lstrlen((LPSTR)TabNumber[tN].BufferName.c_str());
				}
			TabCtrl_SetItem(TabControl->hWnd,counter,&TabNumber[counter].tabitem); // Обновляем вкладку;
			TabCtrl_GetItemRect(TabControl->hWnd,counter,&rctab);
			SendMessage(TabControl->hWnd,WM_LBUTTONUP,rctab.left,rctab.top);
			SetFocus(TabNumber[counter].hwndScintilla);
			TitleBuf = (""); 
			PrintFileToPrinter((LPSTR)TabNumber[counter].BufferName.c_str());
		}
	} 
	else 
	{
		PrintFileToPrinter((LPSTR)TabNumber[counter].BufferName.c_str());
	}
}

/* Функция закрывает активную вкладку /File/Close/ */
int FileClose(WPARAM wPar) 
{
	tabN = TabCtrl_GetItemCount(TabControl->hWnd);
	if(tabN == 1) 
	{
		int mesSF;
		int mesBox = MessageBox(ParentWindow->hWnd,"Save file now?","JaeEditor",MB_YESNO | MB_ICONQUESTION);
		switch(mesBox) 
		{
			case IDYES:
				switch(mesBox) 
				{
					case IDYES:
						if(GetSaveFileName(&ParentWindow->ofn)==true) DLGSAVEFILE();

						PostQuitMessage(0);
						DelNew();
						break;
					case IDNO:
						PostQuitMessage(0);
						DelNew();
						break;
					default: return mesBox;
				}
			break;
			case IDNO:
				PostQuitMessage(0);
				DelNew();
				break;
			default: return mesBox;
		}
	} 
	else 
	{
		counter = TabCtrl_GetCurSel(TabControl->hWnd);
		if(wPar == ID_CLOSE || wPar == 0) 
		{
			int LenTxt = GetWindowTextLength(TabNumber[counter].hwndScintilla);
			if(LenTxt == 0) 
			{
				CloseTab();
			} 
			else 
			{
				int mesSF;
				int mesBox = MessageBox(ParentWindow->hWnd,"Save file now?","JaeEditor",MB_YESNO | MB_ICONQUESTION);
				switch(mesBox) 
				{
					case IDYES:
						if(mesSF = GetSaveFileName(&ParentWindow->ofn)==true) 
						{
							DLGSAVEFILE();
							switch(mesSF) 
							{
								case 1:
									CloseTab();
								break;
								default:
									return mesSF;
							}
						} 
						else 
						{
							return 0;
						}
					break;
					case IDNO:
						CloseTab();
					break;
					default:
						return mesBox;
				}
			}
		}
		return false;
	}
}


/* /File/CloseAll/ */
void FileCloseAll(WPARAM Par) 
{
	for(int i = TabNumber.size()-1; i >= 0; i--)
	{
		TabCtrl_SetCurSel(TabControl->hWnd, i);
		for(int u = 0 ; u < TabNumber.size(); u++) 
		{
			ShowWindow(TabNumber[u].hwndScintilla,SW_HIDE);
			ShowWindow(TabNumber[u].Output,SW_HIDE);
		}
		ShowWindow(TabNumber[i].hwndScintilla,SW_SHOW);
		ShowWindow(TabNumber[i].Output,SW_SHOW);

		if(TabNumber[i].FileInfo.size() != 0)
		{
			FileSave();
			rvalue.SaveOpenedFile(TabNumber[i].FileInfo, std::to_string(i));
		}
		else 
		{
			int mesBox = MessageBox(ParentWindow->hWnd,"Save file now?","JaeEditor",MB_YESNO | MB_ICONQUESTION);
			if (mesBox == 6)
			{
				if(GetSaveFileName(&ParentWindow->ofn)==true) DLGSAVEFILE();
				if(strlen(ParentWindow->ofn.lpstrFile) != 0) rvalue.SaveOpenedFile(ParentWindow->ofn.lpstrFile, std::to_string(i));		
				else rvalue.SaveOpenedFile("", std::to_string(i));
			}
			else
			{
				rvalue.SaveOpenedFile("", std::to_string(i));
			}
		}
	}
	PostQuitMessage(0);
	DelNew();
}

/* /File/Save as/ */
int FileSaveAs() {
	if (GetSaveFileName(&ParentWindow->ofn)==TRUE) 
	{
		counter = TabCtrl_GetCurSel(TabControl->hWnd);
		DLGSAVEFILE();
		TitleBuf = ParentWindow->ofn.lpstrFile;
		TabNumber[counter].FileInfo = ParentWindow->ofn.lpstrFile;
		FileName();
			if(TabNumber[counter].BufferName.length() == 0) 
			{
				TabNumber[counter].tabitem.pszText = "Untitled";
				TabNumber[counter].tabitem.cchTextMax = 8;
			} 
			else 
			{
				TabNumber[counter].tabitem.pszText = (LPSTR)TabNumber[counter].BufferName.c_str();
				TabNumber[counter].tabitem.cchTextMax = lstrlen((LPSTR)TabNumber[counter].BufferName.c_str());
			}
		TabCtrl_SetItem(TabControl->hWnd,counter,&TabNumber[counter].tabitem); // Обновляем вкладку;
		TabCtrl_GetItemRect(TabControl->hWnd,counter,&rctab);
		SendMessage(TabControl->hWnd,WM_LBUTTONUP,rctab.left,rctab.top);
		TitleBuf = (""); 
	}
	return 0;
}

/* Функция проверяет на совпадение пути файла который пользователь собирается
открыть с уже открытыми, если будет совпадения файл открыт не будет */
int Overlap(string path_) 
{
	for(int ol_ = 0; ol_ < TabNumber.size(); ol_++) 
	{
		if(TabNumber[ol_].FileInfo == path_) 
		{
			return 8;
		}
	}
}

void Toggle_a_bookmark(int Line) {
	int c_break = 0;
	int per;
	counter = TabCtrl_GetCurSel(TabControl->hWnd);
	for(int cc_ = 0; cc_ < TabNumber[counter].break_points.size(); cc_++) 
	{ 
		/* Сравниваем с уже существующими закладками, чтобы узнать,
		хочет пользователь добавить закладку или удалить уже существующую */
	   	if(TabNumber[counter].break_points.at(cc_) != Line) 
		{
			c_break = 0;
			SendEditor(SCI_MARKERDELETE,Line,MARK_BOOKMARK); 
		} 
		else 
		{
			c_break = 1; /* Если закладка в этой строке уже существует */
			per = cc_;
			break;
		}
	}
	if(c_break == 1) /* Удаляем закладку */
	{   
		SendEditor(SCI_MARKERDELETE,Line,MARK_BOOKMARK);
		TabNumber[counter].break_points.erase(TabNumber[counter].break_points.begin()+per);
	} 
	else /* Добавляем закладку */
	{	
		SendEditor(SCI_MARKERADD,Line,MARK_BOOKMARK);
		TabNumber[counter].break_points.push_back(Line);
	}
}

void Clear_all_in_the_current_file() 
{
	counter = TabCtrl_GetCurSel(TabControl->hWnd);
	for(int rt_ = 0; rt_<TabNumber[counter].break_points.size(); rt_) 
	{
		SendEditor(SCI_MARKERDELETE, TabNumber[counter].break_points.at(rt_), MARK_BOOKMARK); 
		TabNumber[counter].break_points.erase(TabNumber[counter].break_points.begin() + rt_);
	}
}

void Clear_all_in_all_files() 
{
	int newActiveTab = TabCtrl_GetCurSel(TabControl->hWnd);;
	for(int _rt=0;_rt<TabNumber.size();_rt++) 
	{
		TabCtrl_SetCurSel(TabControl->hWnd,_rt);
		for(int rt_=0; rt_<TabNumber[_rt].break_points.size(); rt_) 
		{
			SendEditor(SCI_MARKERDELETE,TabNumber[_rt].break_points.at(rt_),MARK_BOOKMARK); 
			TabNumber[_rt].break_points.erase(TabNumber[_rt].break_points.begin()+rt_);
		}
	}
	TabCtrl_SetCurSel(TabControl->hWnd,newActiveTab);
}

void Next_Bookmark() 
{
	int prev = -1;
	counter = TabCtrl_GetCurSel(TabControl->hWnd);
	int line = SendEditor(EM_LINEFROMCHAR, (-1), 0);
	stable_sort(TabNumber[counter].break_points.begin(),TabNumber[counter].break_points.end());
	for(int num = 0; num < TabNumber[counter].break_points.size();num++) 
	{
		if(line == TabNumber[counter].break_points.at(num)) 
		{
			prev = num + 1; 
			break;
		}
	}
	if(prev != -1) 
	{
		if(prev >= TabNumber[counter].break_points.size()) prev--;
		SendEditor(SCI_GOTOLINE,TabNumber[counter].break_points.at(prev),0);
	} 
	else 
	{
		for(int t_ = 0; t_ < TabNumber[counter].break_points.size(); t_++) 
		{
			if(line < TabNumber[counter].break_points.at(t_)) 
			{
				SendEditor(SCI_GOTOLINE,TabNumber[counter].break_points.at(t_),0);
				break;
			}
		}
	}
}

void Previous_Bookmark() 
{
	int prev = -1;
	counter = TabCtrl_GetCurSel(TabControl->hWnd);
	int line = SendEditor(EM_LINEFROMCHAR, (-1), 0);
	stable_sort(TabNumber[counter].break_points.begin(),TabNumber[counter].break_points.end());
	for(int num = 0; num < TabNumber[counter].break_points.size();num++) 
	{
		if(line == TabNumber[counter].break_points.at(num)) 
		{
			prev = num - 1; 
			break;
		}
	}
	if(prev != -1) 
	{
		SendEditor(SCI_GOTOLINE,TabNumber[counter].break_points.at(prev),0);
	} 
	else 
	{
		for(int t_ = TabNumber[counter].break_points.size()-1; t_ >= 0; t_--) 
		{
			if(line > TabNumber[counter].break_points.at(t_)) 
			{
				SendEditor(SCI_GOTOLINE,TabNumber[counter].break_points.at(t_),0);
				break;
			}
		}
	}
}

/* Функция добавляет новый проект */
void Add_Project(char *Name) 
{
	counter = TabCtrl_GetCurSel(TabControl->hWnd);
	int gettextlength = GetWindowTextLength(TabNumber[counter].hwndScintilla);
	if(gettextlength == 0) 
	{
		SendEditor(SCI_SETTEXT,0,(LPARAM)Name); 
		FileSaveAs();
	} 
	else 
	{
		NewTab();
		SendEditor(SCI_SETTEXT,0,(LPARAM)Name); 
		FileSaveAs();
	}
	Inc_(); 
	SetFocus(TabNumber[counter].hwndScintilla);
}

inline void Search_in_folder_SDK() {
	char path[150] = {0};
	GetModuleFileName(NULL,path,150); /* Получаем полный путь к исполняемому файлу, т.к. в той же папке лежит prototype.h */
	string path_to_the_exe2 = path; /* Полученный путь заносим в string, что бы проще было получить только путь, без .exe */
	int posit = path_to_the_exe2.rfind("\\");
	path_to_the_exe2.erase(posit + 1,path_to_the_exe2.length());
	path_to_the_exe2 += "prototype.h";
	char path_to_the_inc_API[255] = {0};
	strcpy(path_to_the_inc_API,path_to_the_exe2.c_str());
	/* Читаем из файла */
	FILE * pFile,ptmp;
	pFile = fopen(path_to_the_inc_API,"r");
	long lSize;
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind(pFile);
	char* _buffer = new char[lSize];
	ZeroMemory(_buffer,lSize);
	char str [1000] = {0};
	while(fgets(_buffer,lSize,pFile)) 
	{
		sscanf_s(_buffer,"%[^(]",str,1000);
		api2 += str;
		api2_name.push_back(str);
		if(api2[api2.size()-1] != ' ') api2 += " ";	
		sscanf_s(_buffer,"%[^;]",str,1000);
		string str_ = str;
		int res = 0;
		do 
		{
			res = str_.find(",",res);
			if(res != -1) 
			{
				res++; 
				str_.insert(res,"\n");
			}
		} while (res != -1);
		prototype_api2.push_back(str_);
	}
	if(api2[api2.size()-1] == ' ') api2.erase(api2.size()-1);
	fclose(pFile);
	delete[] _buffer;
}

void Inc_() 
{
	int count = TabCtrl_GetCurSel(TabControl_TrV->hWnd);
	if(count == 0) 
	{
		ShowWindow(AllInc_TrV->hWnd,SW_HIDE);
		ShowWindow(TreeView_R->hWnd,SW_HIDE);
		ShowWindow(TreeView_N->hWnd,SW_SHOW);
	} 
	else if(count == 1) 
	{
		ShowWindow(TreeView_N->hWnd,SW_HIDE);
		ShowWindow(TreeView_R->hWnd,SW_HIDE);
		ShowWindow(AllInc_TrV->hWnd,SW_SHOW);
	} 
	else if(count == 2) 
	{
		ShowWindow(TreeView_N->hWnd,SW_HIDE);
		ShowWindow(TreeView_R->hWnd,SW_SHOW);
		ShowWindow(AllInc_TrV->hWnd,SW_HIDE);
	}
	if(Flag_for_the_TreeView != 1) CreateThread(0,0,Thread_for_the_TreeView,(LPVOID)count,0,0); /* Поток обновления дерева */
}

/* Функция выствляет маркеры для свёртки текста */
void MarkersAdd() 
{
	int iLineCount = SendEditor(SCI_GETLINECOUNT,0,0);
	for(int i = 0; i < iLineCount; i++) 
	{
		int iLineLength = SendEditor(SCI_LINELENGTH,i,0)+1;
		char *txt = new char[iLineLength];
		if(txt) 
		{
			ZeroMemory(txt,iLineLength);
			SendEditor(SCI_GETLINE,i,(LPARAM)txt);
			if(strstr(txt,"data import")||strstr(txt,"dialog ")||strstr(txt,"proc ")||strstr(txt,"start:")
				||strstr(txt,"struct")||strstr(txt,"if ")||strstr(txt,"virtual")||strstr(txt,"repeat ")||strstr(txt,".repeat")) 
			{
				SendEditor(SCI_SETFOLDLEVEL,i, SC_FOLDLEVELBASE | SC_FOLDLEVELHEADERFLAG);
				int iExpanded = SendEditor(SCI_GETFOLDEXPANDED,i,0);
				if(iExpanded == 1) 
				{
					SendEditor(SCI_MARKERDELETE,i,-1);
					SendEditor(SCI_MARKERADD,i,SC_MARKNUM_FOLDEROPEN);
				} 
				else if(iExpanded == 0)
				{
					SendEditor(SCI_MARKERDELETE,i,-1);
					SendEditor(SCI_MARKERADD,i,SC_MARKNUM_FOLDER);
				}
			} 
			else if(strstr(txt,"end data")||strstr(txt,"enddialog")||strstr(txt,"endp")||strstr(txt,".end start")
				||strstr(txt,"ends")||strstr(txt,"end if")||strstr(txt,"end virtual")||strstr(txt,"end repeat")||strstr(txt,".until")) 
			{
				SendEditor(SCI_SETFOLDLEVEL,i,SC_FOLDLEVELBASE);
				SendEditor(SCI_MARKERADD,i,SC_MARKNUM_FOLDERTAIL);
			} 
			else 
			{
				SendEditor(SCI_SETFOLDLEVEL,i, SC_FOLDLEVELBASE | SC_FOLDLEVELWHITEFLAG);
				SendEditor(SCI_MARKERADD,i,SC_MARKNUM_FOLDERSUB);	
			}
		}
		delete[] txt;
	}
}

/* Переход к выбранному элементу в CodeView */
void Goto() 
{
	TVITEM tv_item;
	HTREEITEM item = TreeView_GetSelection(TreeView_R->hWnd);
	ZeroMemory(&tv_item, sizeof(tv_item));
	tv_item.mask = TVIF_TEXT;
		char etr[100] = {0};
		tv_item.pszText = etr;
		tv_item.cchTextMax = 100;
		tv_item.hItem = item;
	TreeView_GetItem(TreeView_R->hWnd,&tv_item);
	string nameitem = tv_item.pszText;
	for(int i = 0; i < InfoTreeView.size(); i++) 
	{
		if(InfoTreeView[i].NameItem == nameitem) 
		{
			SendEditor(SCI_GOTOLINE,InfoTreeView[i].Line,0);
			SendEditor(SCI_SETFIRSTVISIBLELINE,InfoTreeView[i].Line,0);
			break;
		}
	}
}

/* Функция закрывает все вкладки, кроме активной */
void CloseAllButThis()
{
	int activetab = TabCtrl_GetCurSel(TabControl->hWnd);
	for(int i = TabNumber.size()-1; i >= 0; i--)
	{
		if(i != activetab)
		{
			TabCtrl_SetCurSel(TabControl->hWnd, i);
			for(int u = 0 ; u < TabNumber.size(); u++) 
			{
				ShowWindow(TabNumber[u].hwndScintilla,SW_HIDE);
				ShowWindow(TabNumber[u].Output,SW_HIDE);
			}
			ShowWindow(TabNumber[i].hwndScintilla,SW_SHOW);
			ShowWindow(TabNumber[i].Output,SW_SHOW);

			if(TabNumber[i].FileInfo.size() != 0)
			{
				FileSave();
			}
			else 
			{
				int mesBox = MessageBox(ParentWindow->hWnd,"Save file now?","JaeEditor",MB_YESNO | MB_ICONQUESTION);
				if (mesBox == 6)
				{
					if(GetSaveFileName(&ParentWindow->ofn)==true) DLGSAVEFILE();
				}
			}
			CloseTab();
		}
	}
}

/* Функция закрывает все вкладки слева */
void CloseLeft()
{
	int activetab = TabCtrl_GetCurSel(TabControl->hWnd);
	for(int i = activetab - 1; i >= 0; i--)
	{
		TabCtrl_SetCurSel(TabControl->hWnd, i);
		for(int u = 0 ; u < TabNumber.size(); u++) 
		{
			ShowWindow(TabNumber[u].hwndScintilla,SW_HIDE);
			ShowWindow(TabNumber[u].Output,SW_HIDE);
		}
		ShowWindow(TabNumber[i].hwndScintilla,SW_SHOW);
		ShowWindow(TabNumber[i].Output,SW_SHOW);

		if(TabNumber[i].FileInfo.size() != 0)
		{
			FileSave();
		}
		else 
		{
			int mesBox = MessageBox(ParentWindow->hWnd,"Save file now?","JaeEditor",MB_YESNO | MB_ICONQUESTION);
			if (mesBox == 6)
			{
				if(GetSaveFileName(&ParentWindow->ofn)==true) DLGSAVEFILE();
			}
		}
		CloseTab();
	}
}

/* Функция закрывает все вкладки справа */
void CloseRight()
{
	int activetab = TabCtrl_GetCurSel(TabControl->hWnd);
	for(int i = activetab + 1; i < TabNumber.size(); i)
	{
		TabCtrl_SetCurSel(TabControl->hWnd, i);
		for(int u = 0 ; u < TabNumber.size(); u++) 
		{
			ShowWindow(TabNumber[u].hwndScintilla,SW_HIDE);
			ShowWindow(TabNumber[u].Output,SW_HIDE);
		}
		ShowWindow(TabNumber[i].hwndScintilla,SW_SHOW);
		ShowWindow(TabNumber[i].Output,SW_SHOW);

		if(TabNumber[i].FileInfo.size() != 0)
		{
			FileSave();
		}
		else 
		{
			int mesBox = MessageBox(ParentWindow->hWnd,"Save file now?","JaeEditor",MB_YESNO | MB_ICONQUESTION);
			if (mesBox == 6)
			{
				if(GetSaveFileName(&ParentWindow->ofn)==true) DLGSAVEFILE();
			}
		}
		CloseTab();
	}

	TabCtrl_SetCurSel(TabControl->hWnd, activetab);
		for(int u = 0 ; u < TabNumber.size(); u++) 
		{
			ShowWindow(TabNumber[u].hwndScintilla,SW_HIDE);
			ShowWindow(TabNumber[u].Output,SW_HIDE);
		}
		ShowWindow(TabNumber[activetab].hwndScintilla,SW_SHOW);
		ShowWindow(TabNumber[activetab].Output,SW_SHOW);
}