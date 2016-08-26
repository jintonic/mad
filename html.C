using namespace MAD;

void html()
{
    I i;
    THtml html;
    html.SetProductName("MAD");
    html.SetHomepage("http://github.com/jintonic/mad");
    html.SetCharset("UTF-8");
    html.SetAuthorTag("Jing Liu, Jianchen Li");
    html.SetInputDir("../core");
    html.SetOutputDir("../doc/html");
    html.MakeAll();
    cout<<html.GetMacroPath()<<endl;
}
