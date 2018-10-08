using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using YandexLinguistics.NET;
namespace translator
{


    class STranslatator
    {
        YandexLinguistics.NET.Translator tr;
        const string translatorKey = "trnsl.1.1.20180908T193453Z.4e6ef96cfc57ab2b.426eedb5ed88db02cc4e86a64f9469feaa4a0b32";
        public STranslatator()
        {

            tr = new YandexLinguistics.NET.Translator(translatorKey);
        }
        public LangPair GetLangPair(string inputLang, string outputLang)
        {
            LangPair lp = new LangPair();
            #region InputLang
            switch (inputLang)
            {
                case "Азербайджанский":

                    lp.InputLang = Lang.Az;

                    break;
                case "Албанский":

                    lp.InputLang = Lang.Sq;

                    break;
                case "Английский":

                    lp.InputLang = Lang.En;

                    break;
                case "Арабский":
                    break;
                case "Армянский":

                    lp.InputLang = Lang.Hy;

                    break;
                case "Африкаанс":
                    break;
                case "Баскский":
                    break;
                case "Башкирский":
                    break;
                case "Белорусский":

                    lp.InputLang = Lang.Be;

                    break;
                case "Бенгальский":
                    break;
                case "Болгарский":

                    lp.InputLang = Lang.Bg;

                    break;
                case "Боснийский":
                    break;
                case "Валлийский":
                    break;
                case "Венгерский":

                    lp.InputLang = Lang.Hu;

                    break;
                case "Вьетнамский":
                    break;
                case "Гаитянский":
                    break;
                case "Галисийский":
                    break;
                case "Голландский":
                    break;
                case "Греческий":

                    lp.InputLang = Lang.El;

                    break;
                case "Грузинский":
                    break;
                case "Гуджарати":
                    break;
                case "Датский":

                    lp.InputLang = Lang.Da;

                    break;
                case "Иврит":
                    break;
                case "Индонезийский":
                    break;
                case "Ирландский":
                    break;
                case "Исландский":
                    break;
                case "Испанский":

                    lp.InputLang = Lang.Es;

                    break;
                case "Итальянский":

                    lp.InputLang = Lang.It;

                    break;
                case "Казахский":
                    break;
                case "Каннада":
                    break;
                case "Каталанский":

                    lp.InputLang = Lang.Ca;

                    break;
                case "Киргизский":
                    break;
                case "Китайский":
                    break;
                case "Корейский":
                    break;
                case "Латынь":
                    break;
                case "Латышский":

                    lp.InputLang = Lang.Lv;

                    break;
                case "Литовский":

                    lp.InputLang = Lang.Lt;

                    break;
                case "Македонский":

                    lp.InputLang = Lang.Mk;

                    break;
                case "Малагасийский":
                    break;
                case "Малайский":
                    break;
                case "Мальтийский":
                    break;
                case "Монгольский":
                    break;
                case "Немецкий":

                    lp.InputLang = Lang.De;

                    break;
                case "Норвежский":

                    lp.InputLang = Lang.No;

                    break;
                case "Панджаби":
                    break;
                case "Персидский":
                    break;
                case "Польский":

                    lp.InputLang = Lang.Pl;

                    break;
                case "Португальский":

                    lp.InputLang = Lang.Pt;

                    break;
                case "Румынский":

                    lp.InputLang = Lang.Ro;

                    break;
                case "Русский":

                    lp.InputLang = Lang.Ru;

                    break;
                case "Сербский":

                    lp.InputLang = Lang.Sr;

                    break;
                case "Сингальский":
                    break;
                case "Словацкий":

                    lp.InputLang = Lang.Sk;

                    break;
                case "Словенский":

                    lp.InputLang = Lang.Sl;

                    break;
                case "Суахили":
                    break;
                case "Тагальский":
                    break;
                case "Таджикский":
                    break;
                case "Тайский":
                    break;
                case "Тамильский":
                    break;
                case "Татарский":
                    break;
                case "Турецкий":

                    lp.InputLang = Lang.Tr;

                    break;
                case "Удмуртский":
                    break;
                case "Узбекский":
                    break;
                case "Украинский":

                    lp.InputLang = Lang.Uk;

                    break;
                case "Урду":
                    break;
                case "Финский":

                    lp.InputLang = Lang.Fi;

                    break;
                case "Французский":

                    lp.InputLang = Lang.Fr;

                    break;
                case "Хорватский":

                    lp.InputLang = Lang.Hr;

                    break;
                case "Хинди":
                    break;
                case "Чешский":

                    lp.InputLang = Lang.Cs;

                    break;
                case "Шведский":

                    lp.InputLang = Lang.Sv;

                    break;
                case "Эльфийский (cиндарин)":
                    break;
                case "Эстонский":

                    lp.InputLang = Lang.Et;

                    break;
                case "Японский":
                    break;
            }

            #endregion
            #region OutputLang

            switch (outputLang)
            {
                case "Азербайджанский":

                    lp.OutputLang = Lang.Az;

                    break;
                case "Албанский":

                    lp.OutputLang = Lang.Sq;

                    break;
                case "Английский":

                    lp.OutputLang = Lang.En;

                    break;
                case "Арабский":
                    break;
                case "Армянский":

                    lp.OutputLang = Lang.Hy;

                    break;
                case "Африкаанс":
                    break;
                case "Баскский":
                    break;
                case "Башкирский":
                    break;
                case "Белорусский":

                    lp.OutputLang = Lang.Be;

                    break;
                case "Бенгальский":
                    break;
                case "Болгарский":

                    lp.OutputLang = Lang.Bg;

                    break;
                case "Боснийский":
                    break;
                case "Валлийский":
                    break;
                case "Венгерский":

                    lp.OutputLang = Lang.Hu;

                    break;
                case "Вьетнамский":
                    break;
                case "Гаитянский":
                    break;
                case "Галисийский":
                    break;
                case "Голландский":
                    break;
                case "Греческий":

                    lp.OutputLang = Lang.El;

                    break;
                case "Грузинский":
                    break;
                case "Гуджарати":
                    break;
                case "Датский":

                    lp.OutputLang = Lang.Da;

                    break;
                case "Иврит":
                    break;
                case "Индонезийский":
                    break;
                case "Ирландский":
                    break;
                case "Исландский":
                    break;
                case "Испанский":

                    lp.OutputLang = Lang.Es;

                    break;
                case "Итальянский":

                    lp.OutputLang = Lang.It;

                    break;
                case "Казахский":
                    break;
                case "Каннада":
                    break;
                case "Каталанский":

                    lp.OutputLang = Lang.Ca;

                    break;
                case "Киргизский":
                    break;
                case "Китайский":
                    break;
                case "Корейский":
                    break;
                case "Латынь":
                    break;
                case "Латышский":

                    lp.OutputLang = Lang.Lv;

                    break;
                case "Литовский":

                    lp.OutputLang = Lang.Lt;

                    break;
                case "Македонский":

                    lp.OutputLang = Lang.Mk;

                    break;
                case "Малагасийский":
                    break;
                case "Малайский":
                    break;
                case "Мальтийский":
                    break;
                case "Монгольский":
                    break;
                case "Немецкий":

                    lp.OutputLang = Lang.De;

                    break;
                case "Норвежский":

                    lp.OutputLang = Lang.No;

                    break;
                case "Панджаби":
                    break;
                case "Персидский":
                    break;
                case "Польский":

                    lp.OutputLang = Lang.Pl;

                    break;
                case "Португальский":

                    lp.OutputLang = Lang.Pt;

                    break;
                case "Румынский":

                    lp.OutputLang = Lang.Ro;

                    break;
                case "Русский":

                    lp.OutputLang = Lang.Ru;

                    break;
                case "Сербский":

                    lp.OutputLang = Lang.Sr;

                    break;
                case "Сингальский":
                    break;
                case "Словацкий":

                    lp.OutputLang = Lang.Sk;

                    break;
                case "Словенский":

                    lp.OutputLang = Lang.Sl;

                    break;
                case "Суахили":
                    break;
                case "Тагальский":
                    break;
                case "Таджикский":
                    break;
                case "Тайский":
                    break;
                case "Тамильский":
                    break;
                case "Татарский":
                    break;
                case "Турецкий":

                    lp.OutputLang = Lang.Tr;

                    break;
                case "Удмуртский":
                    break;
                case "Узбекский":
                    break;
                case "Украинский":

                    lp.OutputLang = Lang.Uk;

                    break;
                case "Урду":
                    break;
                case "Финский":

                    lp.OutputLang = Lang.Fi;

                    break;
                case "Французский":

                    lp.OutputLang = Lang.Fr;

                    break;
                case "Хорватский":

                    lp.OutputLang = Lang.Hr;

                    break;
                case "Хинди":
                    break;
                case "Чешский":

                    lp.OutputLang = Lang.Cs;

                    break;
                case "Шведский":

                    lp.OutputLang = Lang.Sv;

                    break;
                case "Эльфийский (cиндарин)":
                    break;
                case "Эстонский":

                    lp.OutputLang = Lang.Et;

                    break;
                case "Японский":
                    break;
            }

            #endregion
            return lp;
        }
        public string Translator(string wordToTranslate, LangPair langPair)
        {
            return tr.Translate(wordToTranslate, langPair).Text;
        }
    }
}
