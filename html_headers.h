//---------------------------------------------------------------------------
#ifndef html_headersH
#define html_headersH

const wchar_t *itm_hdr =
L"<html>\
<head><meta http-equiv=\"Content-Type\" content=\"text/html\" charset=\"utf-8\">\
<title>��������� �������</title></head>\
<style>\
body\
{\
background-color:#FFFFFF;\
max-width:800px;\
padding:0px;\
margin:0px auto;\
}\
</style>\
<br>\
<body>\
<center>\
<form method=\"post\" action=\"/\">\
<p><button style=\"width:100px;height:25px\" type=\"submit\">�� �������</button></p>\
</form>\
<form method=\"post\" action=\"items.html\">\
<p><button style=\"width:100px;height:25px\" type=\"submit\">�� ������</button></p>\
</form>\
<br>\
<table border=\"1\">\
<caption><h2>��������� �������</h2></caption>\
<tr><th>����������� �</th><th>������� �</th><th>������</th>\
<th>������</th><th>������</th><th>��� �����</th><th></th><th></th></tr>";

const wchar_t *hist_hdr =
L"<html>\
<head><meta http-equiv=\"Content-Type\" content=\"text/html\" charset=\"utf-8\">\
<title>��������� �������</title></head>\
<style>\
body\
{\
background-color:#FFFFFF;\
max-width:800px;\
padding:0px;\
margin:0px auto;\
}\
</style>\
<br>\
<body>\
<center>\
<form method=\"post\" action=\"/\">\
<p><button style=\"width:100px;height:25px\" type=\"submit\">�� �������</button></p>\
</form>\
<form method=\"post\" action=\"/history.html\">\
<p><button style=\"width:100px;height:25px\" type=\"submit\">��䳿</button></p>\
</form>\
<br>\
<table border=\"1\">\
<caption><h2>��������� �������</h2></caption>\
<tr><th>����</th><th>����������� �</th><th>������� �</th>\
<th>������</th><th>�����</th><th>��������</th></tr>";

const wchar_t *edit_itm_hdr =
L"<html>\
<head><meta http-equiv=\"Content-Type\" content=\"text/html\" charset=\"utf-8\">\
<title>��������� �������</title></head>\
<style>\
body\
{\
background-color:#FFFFFF;\
max-width:800px;\
padding:0px;\
margin:0px auto;\
}\
</style>\
<br>\
<body>\
<center>\
<form method=\"post\" action=\"/\">\
<p><button style=\"width:100px;height:25px\" type=\"submit\">�� �������</button></p>\
</form>\
<form method=\"post\" action=\"items.html\">\
<p><button style=\"width:100px;height:25px\" type=\"submit\">�� ������</button></p>\
</form>\
<form method=\"post\" action=\"item.html\">\
<p><button style=\"width:100px;height:25px\" type=\"submit\">�� �������</button></p>\
</form>\
<form method=\"post\" action=\"set_item.html\">\
<br>\
<table border=\"1\">\
<caption><h2>��������� �������</h2></caption>\r\n\
<tr><th></th><th>����������� �</th><th>������� �</th><th>������</th><th>���� �������</th></tr>";

const wchar_t *login_hdr =
L"<html>\
<head><meta http-equiv=\"Content-Type\" content=\"text/html\" charset=\"utf-8\">\
<title>�����������</title></head>\
<style>\
body\
{\
background-color:#FFFFFF;\
max-width:800px;\
padding:0px;\
margin:0px auto;\
}\
</style>\
<body>\
<center>\
<h2>������ ��� AuthID</h2>\
<form method=\"post\" action=\"/auth.html\">\
<p><input type=\"text\" name=\"login\"></input></p>\
<p><input type=\"password\" name=\"pass\"></input></p>\
<p><button style=\"width:100px;height:25px\" type=\"submit\">�����</button></p>\
</form>\
</center>\
</body>\
</html>";

const wchar_t *users_hdr =
L"<html>\r\n\
<head><meta http-equiv=\"Content-Type\" content=\"text/html\" charset=\"utf-8\">\
<title>��������� �������</title></head>\
<style>\
body\
{\
background-color:#FFFFFF;\
max-width:800px;\
padding:0px;\
margin:0px auto;\
}\
</style>\
<br>\
<body>\
<center>\
<form method=\"post\" action=\"/\">\
<p><button style=\"width:200px;height:25px\" type=\"submit\">�� �������</button></p>\
</form>\
<form method=\"post\" action=\"admin.html\">\
<p><button style=\"width:200px;height:25px\" type=\"submit\">�������������</button></p>\
</form>\
<br>\
<table border=\"1\">\
<caption><h2>��������� �������</h2></caption>\
<tr><th>ID</th><th>����</th><th>��'�</th><th>����</th><th></th><th></th></tr>";

const wchar_t *sessions_hdr =
L"<html>\
<head><meta http-equiv=\"Content-Type\" content=\"text/html\" charset=\"utf-8\">\
<title>��������� �������</title></head>\
<style>\
body\
{\
background-color:#FFFFFF;\
max-width:800px;\
padding:0px;\
margin:0px auto;\
}\
</style>\
<br>\
<body>\
<center>\
<form method=\"post\" action=\"/\">\
<p><button style=\"width:200px;height:25px\" type=\"submit\">�� �������</button></p>\
</form>\
<form method=\"post\" action=\"admin.html\">\
<p><button style=\"width:200px;height:25px\" type=\"submit\">�������������</button></p>\
</form>\
<br>\
<table border=\"1\">\
<caption><h2>��������� �������</h2></caption>\
<tr><th>ID</th><th>UserID</th><th>���</th><th>��������</th><th></th></tr>";

const wchar_t *set_pwd_hdr =
L"<html>\r\n\
<head><meta http-equiv=\"Content-Type\" content=\"text/html\" charset=\"utf-8\">\
<title>��������� �������</title></head>\r\n\
<style>\
body\
{\
background-color:#FFFFFF;\
max-width:800px;\
padding:0px;\
margin:0px auto;\
}\
</style>\
<br>\
<body>\
<center>\
<form method=\"post\" action=\"/\">\
<p><button style=\"width:200px;height:25px\" type=\"submit\">�� �������</button></p>\
</form>\
<form method=\"post\" action=\"admin.html\">\
<p><button style=\"width:200px;height:25px\" type=\"submit\">�������������</button></p>\
</form>\
<p><h3>������ ����� ������</h3></p>\
<form method=\"post\" action=\"pwd.html\">\
<input type=\"hidden\" name=\"id\" value=[***]></input>\
<input type=\"password\" name=\"new_pwd\"></input>\
<p><button style=\"width:180px;height:25px\" type=\"submit\">���������� ������</button></p>\
</form>\
</center>\
<br>\
</body>\
<br>\
</html>";

const wchar_t *change_pwd_hdr =
L"<html>\r\n\
<head><meta http-equiv=\"Content-Type\" content=\"text/html\" charset=\"utf-8\">\
<title>��������� �������</title></head>\r\n\
<style>\
body\
{\
background-color:#FFFFFF;\
max-width:800px;\
padding:0px;\
margin:0px auto;\
}\
</style>\
<br>\
<body>\
<center>\
<form method=\"post\" action=\"/\">\
<p><button style=\"width:200px;height:25px\" type=\"submit\">�� �������</button></p>\
</form>\
<p><h3>���� ������</h3></p>\
<form method=\"post\" action=\"pwd.html\">\
<input type=\"hidden\" name=\"id\" value=[***]></input>\
<p><h3>������ ������ ������</h3></p>\
<input type=\"password\" name=\"old_pwd\"></input>\
<p><h3>������ ����� ������</h3></p>\
<input type=\"password\" name=\"new_pwd\"></input>\
<p><h3>�������� ����� ������</h3></p>\
<input type=\"password\" name=\"new_pwd_confirm\"></input>\
<p><button style=\"width:180px;height:25px\" type=\"submit\">������ ������</button></p>\
</form>\
</center>\
<br>\
</body>\
<br>\
</html>";

const wchar_t *logs_hdr =
L"<html>\
<head><meta http-equiv=\"Content-Type\" content=\"text/html\" charset=\"utf-8\">\
<title>��������� �������</title></head>\
<style>\
body\
{\
background-color:#FFFFFF;\
max-width:800px;\
padding:0px;\
margin:0px auto;\
}\
</style>\
<br>\
<body>\
<center>\
<form method=\"post\" action=\"/\">\
<p><button style=\"width:200px;height:25px\" type=\"submit\">�� �������</button></p>\
</form>\
<form method=\"post\" action=\"admin.html\">\
<p><button style=\"width:200px;height:25px\" type=\"submit\">�������������</button></p>\
</form>\
<form method=\"post\" action=\"log.html\">\
<p><button style=\"width:200px;height:25px\" type=\"submit\">�����</button></p>\
</form>\
</center>\
<br>\
[***]\
</body>\
<br>\
</html>";

const wchar_t *locations_hdr =
L"<html>\
<head><meta http-equiv=\"Content-Type\" content=\"text/html\" charset=\"utf-8\">\
<title>��������� �������</title></head>\
<style>\
body\
{\
background-color:#FFFFFF;\
max-width:800px;\
padding:0px;\
margin:0px auto;\
}\
</style>\
<br>\
<body>\
<center>\
<form method=\"post\" action=\"/\">\
<p><button style=\"width:200px;height:25px\" type=\"submit\">�� �������</button></p>\
</form>\
<form method=\"post\" action=\"admin.html\">\
<p><button style=\"width:200px;height:25px\" type=\"submit\">�������������</button></p>\
</form>\
<br>\
<table border=\"1\">\
<caption><h2>��������� �������</h2></caption>\
<tr><th>ID</th><th>������</th><th>������</th><th></th><th></th></tr>";

const wchar_t *location_hdr =
L"<html>\
<head><meta http-equiv=\"Content-Type\" content=\"text/html\" charset=\"utf-8\">\
<title>��������� �������</title></head>\
<style>\
body\
{\
background-color:#FFFFFF;\
max-width:800px;\
padding:0px;\
margin:0px auto;\
}\
</style>\
<br>\
<body>\
<center>\
<form method=\"post\" action=\"/\">\
<p><button style=\"width:200px;height:25px\" type=\"submit\">�� �������</button></p>\
</form>\
<form method=\"post\" action=\"admin.html\">\
<p><button style=\"width:200px;height:25px\" type=\"submit\">�������������</button></p>\
</form>\
<form method=\"post\" action=\"locations.html\">\
<p><button style=\"width:200px;height:25px\" type=\"submit\">�����</button></p>\
</form>\
<br>\
</form>\
<form method=\"post\" action=\"set_loc.html\">";
//---------------------------------------------------------------------------
#endif
