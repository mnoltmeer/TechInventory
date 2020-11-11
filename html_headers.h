//---------------------------------------------------------------------------
#ifndef html_headersH
#define html_headersH

const wchar_t *itm_hdr =
L"<html>\
<head><meta http-equiv=\"Content-Type\" content=\"text/html\" charset=\"utf-8\">\
<title>Результат виборки</title></head>\
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
<p><button style=\"width:100px;height:25px\" type=\"submit\">На головну</button></p>\
</form>\
<form method=\"post\" action=\"items.html\">\
<p><button style=\"width:100px;height:25px\" type=\"submit\">До вибору</button></p>\
</form>\
<br>\
<table border=\"1\">\
<caption><h2>Результат виборки</h2></caption>\
<tr><th>Інвентарний №</th><th>Серійний №</th><th>Модель</th>\
<th>Індекс</th><th>Адреса</th><th>Дані змінив</th><th></th><th></th></tr>";

const wchar_t *hist_hdr =
L"<html>\
<head><meta http-equiv=\"Content-Type\" content=\"text/html\" charset=\"utf-8\">\
<title>Результат виборки</title></head>\
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
<p><button style=\"width:100px;height:25px\" type=\"submit\">На головну</button></p>\
</form>\
<form method=\"post\" action=\"/history.html\">\
<p><button style=\"width:100px;height:25px\" type=\"submit\">Події</button></p>\
</form>\
<br>\
<table border=\"1\">\
<caption><h2>Результат виборки</h2></caption>\
<tr><th>Дата</th><th>Інвентарний №</th><th>Серійний №</th>\
<th>Модель</th><th>Агент</th><th>Операція</th></tr>";

const wchar_t *edit_itm_hdr =
L"<html>\
<head><meta http-equiv=\"Content-Type\" content=\"text/html\" charset=\"utf-8\">\
<title>Результат виборки</title></head>\
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
<p><button style=\"width:100px;height:25px\" type=\"submit\">На головну</button></p>\
</form>\
<form method=\"post\" action=\"items.html\">\
<p><button style=\"width:100px;height:25px\" type=\"submit\">До вибору</button></p>\
</form>\
<form method=\"post\" action=\"item.html\">\
<p><button style=\"width:100px;height:25px\" type=\"submit\">До переліку</button></p>\
</form>\
<form method=\"post\" action=\"set_item.html\">\
<br>\
<table border=\"1\">\
<caption><h2>Результат виборки</h2></caption>\r\n\
<tr><th></th><th>Інвентарний №</th><th>Серійний №</th><th>Модель</th><th>Нова Локація</th></tr>";

const wchar_t *login_hdr =
L"<html>\
<head><meta http-equiv=\"Content-Type\" content=\"text/html\" charset=\"utf-8\">\
<title>Авторизація</title></head>\
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
<h2>Введіть ваш AuthID</h2>\
<form method=\"post\" action=\"/auth.html\">\
<p><input type=\"text\" name=\"login\"></input></p>\
<p><input type=\"password\" name=\"pass\"></input></p>\
<p><button style=\"width:100px;height:25px\" type=\"submit\">Увійти</button></p>\
</form>\
</center>\
</body>\
</html>";

const wchar_t *users_hdr =
L"<html>\r\n\
<head><meta http-equiv=\"Content-Type\" content=\"text/html\" charset=\"utf-8\">\
<title>Результат виборки</title></head>\
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
<p><button style=\"width:200px;height:25px\" type=\"submit\">На головну</button></p>\
</form>\
<form method=\"post\" action=\"admin.html\">\
<p><button style=\"width:200px;height:25px\" type=\"submit\">Адміністрування</button></p>\
</form>\
<br>\
<table border=\"1\">\
<caption><h2>Результат виборки</h2></caption>\
<tr><th>ID</th><th>Логін</th><th>Ім'я</th><th>Роль</th><th></th><th></th></tr>";

const wchar_t *sessions_hdr =
L"<html>\
<head><meta http-equiv=\"Content-Type\" content=\"text/html\" charset=\"utf-8\">\
<title>Результат виборки</title></head>\
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
<p><button style=\"width:200px;height:25px\" type=\"submit\">На головну</button></p>\
</form>\
<form method=\"post\" action=\"admin.html\">\
<p><button style=\"width:200px;height:25px\" type=\"submit\">Адміністрування</button></p>\
</form>\
<br>\
<table border=\"1\">\
<caption><h2>Результат виборки</h2></caption>\
<tr><th>ID</th><th>UserID</th><th>Хеш</th><th>Створено</th><th></th></tr>";

const wchar_t *set_pwd_hdr =
L"<html>\r\n\
<head><meta http-equiv=\"Content-Type\" content=\"text/html\" charset=\"utf-8\">\
<title>Результат виборки</title></head>\r\n\
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
<p><button style=\"width:200px;height:25px\" type=\"submit\">На головну</button></p>\
</form>\
<form method=\"post\" action=\"admin.html\">\
<p><button style=\"width:200px;height:25px\" type=\"submit\">Адміністрування</button></p>\
</form>\
<p><h3>Введіть новий пароль</h3></p>\
<form method=\"post\" action=\"pwd.html\">\
<input type=\"hidden\" name=\"id\" value=[***]></input>\
<input type=\"password\" name=\"new_pwd\"></input>\
<p><button style=\"width:180px;height:25px\" type=\"submit\">Встановити пароль</button></p>\
</form>\
</center>\
<br>\
</body>\
<br>\
</html>";

const wchar_t *change_pwd_hdr =
L"<html>\r\n\
<head><meta http-equiv=\"Content-Type\" content=\"text/html\" charset=\"utf-8\">\
<title>Результат виборки</title></head>\r\n\
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
<p><button style=\"width:200px;height:25px\" type=\"submit\">На головну</button></p>\
</form>\
<p><h3>Зміна паролю</h3></p>\
<form method=\"post\" action=\"pwd.html\">\
<input type=\"hidden\" name=\"id\" value=[***]></input>\
<p><h3>Вкажіть старий пароль</h3></p>\
<input type=\"password\" name=\"old_pwd\"></input>\
<p><h3>Введіть новий пароль</h3></p>\
<input type=\"password\" name=\"new_pwd\"></input>\
<p><h3>Повторіть новий пароль</h3></p>\
<input type=\"password\" name=\"new_pwd_confirm\"></input>\
<p><button style=\"width:180px;height:25px\" type=\"submit\">Змінити пароль</button></p>\
</form>\
</center>\
<br>\
</body>\
<br>\
</html>";

const wchar_t *logs_hdr =
L"<html>\
<head><meta http-equiv=\"Content-Type\" content=\"text/html\" charset=\"utf-8\">\
<title>Результат виборки</title></head>\
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
<p><button style=\"width:200px;height:25px\" type=\"submit\">На головну</button></p>\
</form>\
<form method=\"post\" action=\"admin.html\">\
<p><button style=\"width:200px;height:25px\" type=\"submit\">Адміністрування</button></p>\
</form>\
<form method=\"post\" action=\"log.html\">\
<p><button style=\"width:200px;height:25px\" type=\"submit\">Назад</button></p>\
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
<title>Результат виборки</title></head>\
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
<p><button style=\"width:200px;height:25px\" type=\"submit\">На головну</button></p>\
</form>\
<form method=\"post\" action=\"admin.html\">\
<p><button style=\"width:200px;height:25px\" type=\"submit\">Адміністрування</button></p>\
</form>\
<br>\
<table border=\"1\">\
<caption><h2>Результат виборки</h2></caption>\
<tr><th>ID</th><th>Індекс</th><th>Адреса</th><th></th><th></th></tr>";

const wchar_t *location_hdr =
L"<html>\
<head><meta http-equiv=\"Content-Type\" content=\"text/html\" charset=\"utf-8\">\
<title>Результат виборки</title></head>\
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
<p><button style=\"width:200px;height:25px\" type=\"submit\">На головну</button></p>\
</form>\
<form method=\"post\" action=\"admin.html\">\
<p><button style=\"width:200px;height:25px\" type=\"submit\">Адміністрування</button></p>\
</form>\
<form method=\"post\" action=\"locations.html\">\
<p><button style=\"width:200px;height:25px\" type=\"submit\">Назад</button></p>\
</form>\
<br>\
</form>\
<form method=\"post\" action=\"set_loc.html\">";
//---------------------------------------------------------------------------
#endif
