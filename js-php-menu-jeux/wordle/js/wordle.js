
var lig = 6; //nbr d'essais(lignes)
var col =5;  //nbr de lettre dans le mot (colonnes)

var posLig=0;   //position dans la ligne
var posCol=0;   //position dans la colonne

var scoreActuel = 0;
var niveauActuel = 0;
var finJeu = false;

var indiceUtilise = false; 

var SOLUTION_LIST = ["acier ", "agent", "aider", "aimer", "ainsi", "aller", "amour", "annee", "appel", "apres", "arbre", "armee", "assez", "atome", "aucun", "aussi", "autre", "avant", "avion", "avoir", "balle", "bande", "baton", "blanc", "boire", "boite", "bonne", "bruit", "calme", "carre", "carte", "casse", "cause", "chaud", "cheri", "chien", "choix", "chose", "clair", "comme", "copie", "corde", "corps", "coton", "coupe", "cours", "court", "creer", "crier", "danse", "debit", "debut", "deces", "degre", "dents", "doigt", "donne", "doute", "droit", "drole", "eclat", "ecole", "ecrit", "effet", "entre", "envie", "epais", "etage", "etait", "etape", "etude", "exact", "facon", "faire", "faute", "femme", "ferme", "figue", "filer", "fille", "finir", "fleur", "force", "foret", "forme", "foule", "frais", "frere", "froid", "front", "fruit", "gamme", "garde", "genre", "geste", "glace", "gosse", "grand", "grave", "herbe", "heure", "hiver", "homme", "hotel", "huile", "image", "jambe", "jaune", "jeter", "jeune", "jouer", "jurer", "juste", "large", "leger", "lever", "levre", "libre", "ligne", "liste", "litre", "livre", "lourd", "lutte", "maman", "masse", "matin", "mener", "merci", "merde", "metal", "metre", "mieux", "mille", "mince", "moins", "monde", "moyen", "neige", "notre", "nuage", "objet", "ocean", "odeur", "ombre", "oncle", "ordre", "ouest", "outil", "paire", "passe", "pause", "payer", "peine", "perdu", "petit", "photo", "piece", "pieds", "piste", "place", "plein", "pluie", "poche", "poeme", "poids", "point", "pomme", "porte", "poser", "poste", "pouce", "prier", "quand", "queue", "radio", "rayon", "regle", "reste", "rever", "riche", "rouge", "route", "sable", "salle", "salut", "scene", "score", "siege", "signe", "soeur", "soins", "sorte", "sucre", "suite", "sujet", "super", "table", "taire", "temps", "tenir", "terme", "terre", "tirer", "total", "toute", "train", "trois", "unite", "usine", "vache", "vague", "venir", "verbe", "verre", "vetir", "vieux", "ville", "vingt", "vivre", "voile", "voler", "votre"]

var WORD_LIST = ["abaca", "abale", "abats", "abbes", "abces", "abdos", "abees", "abers", "abeti", "abies", "abime", "ables", "abois", "aboli", "abord", "abots", "about", "aboye", "abras", "abrie", "abris", "abuse", "abute", "abyme", "acais", "acare", "acces", "accon", "accot", "accro", "accru", "accul", "accus", "acere", "achar", "achat", "acheb", "aches", "acide", "acier", "acini", "acmes", "acnes", "acons", "acore", "acras", "acres", "actee", "acter", "actes", "actif", "actus", "aculs", "acyle", "adacs", "adage", "adavs", "addax", "adent", "adieu", "adire", "adjar", "admis", "adnee", "adnes", "adobe", "adonc", "adons", "adore", "adrar", "adret", "adule", "aedes", "aeree", "aerer", "aeres", "aeros", "afare", "afars", "afats", "affin", "affut", "afros", "after", "agace", "agada", "agame", "agami", "agape", "agate", "agave", "agees", "agent", "agglo", "aghas", "agies", "agile", "agios", "agite", "agnat", "agnel", "agnie", "agnis", "agoni", "agora", "agree", "agreg", "agres", "aguis", "ahane", "ahans", "ahuri", "aiche", "aidee", "aider", "aides", "aieul", "aieux", "aigle", "aigre", "aigri", "aigue", "aigus", "ailee", "ailes", "aille", "aimee", "aimer", "aimes", "ainee", "aines", "ainou", "ainsi", "aioli", "airco", "airee", "airer", "aires", "aisee", "aises", "aisys", "ajonc", "ajour", "ajout", "ajuts", "akans", "akene", "akita", "album", "aldin", "aldol", "aleas", "alems", "alene", "aleph", "alese", "alevi", "aleze", "alfas", "algal", "algie", "algol", "algue", "alias", "alibi", "alien", "alios", "alise", "alite", "alize", "allee", "aller", "alles", "alleu", "allez", "allie", "alloc", "almee", "aloes", "alois", "alors", "alose", "alpax", "alpee", "alper", "alpes", "alpha", "alpin", "altea", "alter", "altos", "alule", "alune", "aluni", "aluns", "alvin", "alyas", "alyte", "amans", "amant", "amati", "amble", "ambon", "ambre", "amene", "amere", "amers", "amibe", "amict", "amide", "amies", "amigo", "amine", "amish", "amman", "ammis", "amoks", "amome", "amont", "amour", "amphi", "ample", "ampli", "amuie", "amuir", "amuis", "amuit", "amure", "amuse", "amyle", "anale", "anars", "anaux", "anche", "ancre", "andin", "anees", "anels", "aneth", "anges", "angle", "angon", "angor", "angus", "anier", "anils", "anima", "anime", "anion", "anise", "anite", "anjou", "ankhs", "annal", "annee", "anniv", "anode", "anoli", "anona", "anone", "anons", "ansee", "anses", "antan", "antes", "antre", "aorte", "aoute", "aouts", "apero", "aphte", "apide", "apiol", "apion", "aplat", "apnee", "apode", "appas", "appat", "appel", "appli", "appui", "aprem", "apres", "aptes", "apure", "apyre", "arabe", "arack", "aracs", "araks", "arase", "arbre", "arche", "archi", "archs", "arcon", "ardue", "ardus", "arecs", "arena", "arene", "arete", "argan", "argas", "argol", "argon", "argot", "argue", "argus", "arhat", "arias", "aride", "arien", "arise", "armee", "armer", "armes", "armet", "armon", "arobe", "arole", "arols", "arome", "arque", "arret", "arroi", "arsin", "arsis", "artel", "artys", "arums", "aryen", "aryle", "arzel", "asado", "asana", "asdic", "asics", "asile", "asine", "asins", "aspes", "aspic", "aspis", "asple", "aspre", "asque", "asram", "assai", "assec", "asses", "assez", "assis", "assos", "aster", "astes", "astic", "astis", "astre", "ataca", "atele", "atemi", "athee", "athle", "atipa", "atlas", "atman", "atoca", "atoll", "atome", "atone", "atour", "atout", "atres", "aubes", "aubin", "aucun", "audio", "audit", "augee", "auges", "auget", "aulas", "aulne", "aunee", "auner", "aunes", "auras", "aussi", "autan", "autel", "autos", "autre", "avahi", "avale", "avals", "avant", "avare", "avens", "avent", "avenu", "avere", "avers", "aveux", "avide", "avien", "avili", "avine", "avion", "avise", "aviso", "avive", "avoir", "avoue", "avoye", "avril", "awacs", "awale", "awele", "axant", "axees", "axels", "axene", "axial", "axile", "axoas", "axone", "ayant", "azeri", "azobe", "azore", "azote", "azure", "azurs", "azyme", "babas", "babel", "babil", "babys", "bacha", "bache", "bachi", "bacle", "bacon", "bacul", "badas", "badee", "bader", "bades", "badge", "badin", "baffe", "bafre", "bagad", "bagel", "baggy", "bagne", "bagou", "bague", "bahai", "bahts", "bahut", "baies", "baile", "baine", "bains", "baise", "balai", "balan", "bales", "balle", "balsa", "balte", "bamba", "banal", "banat", "banco", "bancs", "banda", "bande", "bangs", "banjo", "banne", "banni", "banon", "bantu", "baous", "baque", "barbe", "barbu", "barda", "barde", "bards", "barge", "baril", "barjo", "barns", "baron", "barre", "barri", "barye", "barza", "basal", "basee", "baser", "bases", "basic", "basie", "basin", "basir", "basis", "bassa", "basse", "basta", "baste", "batch", "batee", "bater", "bates", "baths", "batie", "batik", "batir", "batis", "baton", "batte", "battu", "bauds", "bauge", "baume", "bavee", "baver", "baves", "bayer", "bayle", "bayou", "bazar", "bazin", "bazou", "beant", "beate", "beats", "beauf", "beaux", "bebes", "bebop", "beche", "becot", "becte", "bedes", "bedon", "begue", "begum", "begus", "behai", "beige", "bekee", "bekes", "belee", "beler", "beles", "belga", "belge", "belle", "belon", "bemba", "bemol", "benef", "benet", "benie", "benin", "benir", "benis", "benit", "benji", "benne", "bento", "berce", "beret", "berge", "berme", "berne", "berot", "beryl", "beryx", "besas", "besef", "beset", "betas", "betee", "betel", "betes", "betie", "betis", "beton", "bette", "beuhs", "beure", "beurk", "beurs", "beuse", "bevue", "bezef", "biais", "biaxe", "bibis", "bible", "bibli", "bibus", "biche", "bicol", "bicot", "bides", "bidet", "bidon", "bidou", "biefs", "biens", "biere", "biffe", "biges", "bigle", "bigor", "bigos", "bigot", "bigre", "bigue", "bijou", "biker", "bilan", "bilee", "biler", "biles", "bilie", "bille", "bills", "bimbo", "bindi", "binee", "biner", "bines", "bingo", "binon", "biome", "biote", "bipas", "bipee", "biper", "bipes", "bique", "birbe", "birrs", "bisee", "biser", "bises", "biset", "bisoc", "bison", "bisou", "bisse", "bitee", "biter", "bites", "bitis", "bitos", "bitte", "bittu", "bitue", "bitus", "biwas", "bizet", "bizou", "bizut", "black", "blaff", "blair", "blame", "blanc", "blaps", "blase", "blast", "blaze", "bleds", "bleme", "blemi", "blese", "blets", "bletz", "bleue", "bleui", "bleus", "blind", "blini", "blitz", "block", "blocs", "blogs", "blond", "bloom", "blots", "blues", "bluet", "bluff", "blush", "blute", "bobby", "bobet", "bobos", "bobun", "bocal", "boche", "bocks", "bodhi", "bodys", "boers", "boete", "boeuf", "boges", "bogey", "bogie", "bogue", "boiar", "boide", "boire", "boise", "boite", "bokit", "bolas", "boldo", "bolee", "bolet", "bolos", "bolus", "bomba", "bombe", "bomee", "bomes", "bomme", "bonde", "bondi", "bonds", "bongo", "bonif", "bonis", "bonne", "bonte", "bonus", "bonze", "books", "booms", "boost", "boots", "borax", "borde", "bordj", "bords", "boree", "bores", "borie", "borin", "borne", "borts", "bosco", "boson", "bosse", "bossu", "botes", "botos", "botox", "botte", "boucs", "boude", "boudi", "boudu", "bouee", "boues", "bouge", "bouif", "boula", "boule", "boume", "boums", "boure", "bourg", "bours", "bouse", "boute", "bouts", "bouzy", "bovin", "bowal", "boxee", "boxer", "boxes", "boxon", "boyau", "brade", "braie", "brais", "brait", "brame", "brand", "brans", "brase", "brava", "brave", "bravi", "bravo", "braye", "break", "brede", "brefs", "brele", "breme", "brens", "brent", "breve", "bribe", "brick", "bride", "briee", "brief", "bries", "briks", "brime", "brins", "brion", "brios", "brise", "brize", "brocs", "brode", "broie", "brols", "brome", "brook", "broue", "broum", "brous", "brout", "broye", "bruie", "bruir", "bruis", "bruit", "brule", "brume", "brune", "bruni", "bruns", "brute", "bruts", "bubon", "buche", "buees", "bugge", "buggy", "bugle", "bugne", "buire", "bulbe", "bulbs", "bulge", "bulle", "bulls", "bulot", "bunas", "buque", "burat", "bures", "burgs", "burin", "burka", "burle", "burne", "buron", "burqa", "buscs", "busee", "buser", "buses", "bushs", "buste", "butee", "buter", "butes", "butin", "butor", "butos", "butte", "buvee", "buzet", "buzze", "byeri", "bytes", "caban", "cabas", "cable", "cabot", "cabre", "cabri", "cabus", "cacao", "cacas", "cacha", "cache", "cacou", "caddy", "cades", "cadet", "cadis", "cador", "cadre", "caduc", "cafes", "cafre", "cafte", "cagee", "cages", "caget", "cagna", "cagne", "cagot", "cagou", "cague", "cahot", "caids", "caieu", "caion", "cairn", "cajan", "cajet", "cajou", "cajun", "cakes", "cakta", "cakti", "calao", "calee", "caler", "cales", "calfs", "calin", "calla", "calle", "calls", "calme", "calmi", "calos", "calot", "calte", "calus", "calva", "cambe", "camee", "cameo", "camer", "cames", "campe", "campo", "camps", "camus", "canal", "canar", "candi", "canee", "caner", "canes", "cange", "canif", "canin", "canna", "canne", "canoe", "canon", "canot", "cante", "cants", "canus", "canut", "caoua", "capas", "capee", "caper", "capes", "capet", "capon", "capos", "capot", "cappa", "capre", "capte", "caque", "carat", "carbo", "carde", "caret", "carex", "cargo", "caria", "carie", "caris", "carme", "carne", "carpe", "carre", "carry", "carte", "carva", "carvi", "carys", "casco", "casee", "caser", "cases", "cashs", "casse", "casta", "caste", "catas", "catch", "cates", "catho", "catie", "catin", "catir", "catis", "caude", "cauri", "cause", "cavas", "cavea", "cavee", "caver", "caves", "cavet", "cavum", "cayes", "cayeu", "cayon", "ceans", "cebes", "cedat", "cedee", "ceder", "cedes", "cedex", "cedis", "cedre", "cegep", "ceint", "celee", "celer", "celes", "cella", "celle", "celte", "celui", "cenes", "cenne", "cense", "cents", "cepee", "cepes", "cerat", "cerce", "cerfs", "cerne", "cesar", "cesse", "ceste", "cetol", "cette", "cezig", "chahs", "chair", "chais", "chale", "champ", "chans", "chant", "chaos", "chape", "chapo", "chars", "chats", "chaud", "chaux", "cheap", "cheba", "chebs", "check", "chefs", "cheik", "chene", "cheni", "chenu", "chere", "cheri", "chers", "cheve", "chiac", "chias", "chics", "chiee", "chien", "chier", "chies", "chile", "chili", "china", "chine", "chino", "chiot", "chipe", "chipo", "chips", "chiro", "choco", "chocs", "choir", "choix", "choke", "chome", "chopa", "chope", "chops", "chore", "chose", "chott", "choux", "choye", "chtis", "chues", "chums", "chute", "chuts", "chvas", "chyle", "chyme", "cible", "cicle", "cidre", "ciels", "cieux", "cigue", "cilie", "cille", "cimes", "cines", "cipal", "cippe", "cipre", "circa", "ciree", "cirer", "cires", "ciron", "cirre", "cirse", "ciste", "citee", "citer", "cites", "cives", "civet", "civil", "clade", "claie", "claim", "clair", "clame", "clamp", "clams", "clans", "clape", "clapi", "claps", "clark", "clash", "clave", "clays", "clean", "clebs", "clefs", "clerc", "click", "clics", "clims", "clins", "clips", "clito", "clive", "clodo", "clone", "clope", "clore", "close", "cloud", "cloue", "cloup", "clous", "clown", "clubs", "clues", "cluse", "coach", "coati", "cobea", "cobee", "cobes", "cobol", "cobra", "cobza", "cocas", "cocci", "coche", "cocon", "cocos", "cocue", "cocus", "codas", "codec", "codee", "coder", "codes", "codex", "codon", "coefs", "coeur", "cogne", "cohue", "coing", "coins", "coirs", "coite", "coits", "cokes", "colas", "colee", "colin", "colis", "colle", "coloc", "colon", "colos", "colts", "colza", "comas", "combe", "combi", "combo", "comma", "comme", "compo", "comte", "concu", "conde", "condo", "cones", "conga", "conge", "conne", "connu", "conso", "conte", "cools", "copal", "copie", "copla", "coppa", "copra", "copte", "coque", "coran", "corbs", "corde", "cores", "corgi", "corme", "corne", "cornu", "coron", "corpo", "corps", "corse", "corso", "cosse", "cossu", "cosys", "cotee", "coter", "cotes", "cotie", "cotir", "cotis", "coton", "cotre", "cotte", "couac", "coude", "couic", "coule", "coupe", "coups", "cours", "court", "couru", "cousu", "coute", "couts", "couve", "couvi", "couvs", "coxal", "coxas", "coxee", "coxer", "coxes", "coyau", "coyer", "crabe", "crack", "cracs", "crade", "crado", "craie", "crame", "crane", "crans", "craps", "crase", "crash", "craus", "craux", "crave", "crawl", "creat", "credo", "creee", "creek", "creer", "crees", "crema", "creme", "crene", "crepe", "crepi", "crepu", "crete", "crets", "creux", "creve", "crias", "cribs", "crics", "criee", "crier", "cries", "crime", "crins", "crise", "criss", "croco", "crocs", "croit", "croix", "crole", "cross", "croup", "crown", "crows", "cruel", "crues", "cruor", "cubee", "cuber", "cubes", "cubis", "cucul", "cucus", "cueva", "cufat", "cuire", "cuirs", "cuite", "cuits", "culee", "culer", "cules", "culex", "culot", "culte", "cumin", "cumul", "cupro", "curee", "curer", "cures", "curie", "curry", "cutis", "cuvee", "cuver", "cuves", "cyans", "cycas", "cycle", "cyclo", "cygne", "cymes", "cyons", "czars", "dabas", "dabes", "daces", "dache", "dadas", "dague", "dahir", "dahls", "dahus", "dails", "daims", "daine", "daira", "dakin", "dalit", "dalle", "dalot", "daman", "damas", "damee", "damer", "dames", "damne", "dance", "dandy", "danio", "danse", "darce", "darde", "dards", "daris", "darne", "daron", "darse", "dashi", "datee", "dater", "dates", "datif", "datte", "daube", "dauws", "dayak", "deale", "deals", "debat", "debet", "debit", "debut", "debye", "decan", "decas", "decca", "deces", "deche", "dechu", "decis", "decks", "decor", "decos", "decri", "decru", "decue", "decus", "dedie", "dedit", "defet", "defie", "defis", "degat", "degel", "degre", "degue", "degun", "deite", "delai", "delco", "delie", "delit", "delot", "delta", "demes", "demie", "demis", "demon", "demos", "denar", "dendi", "denie", "denim", "denis", "dense", "dente", "denti", "dents", "dentu", "denue", "depit", "deplu", "depot", "derby", "derme", "derny", "desir", "desks", "detox", "dette", "deugs", "deuil", "deust", "devie", "devin", "devis", "devon", "devot", "dewar", "dhals", "dhikr", "dhole", "dhoti", "dials", "diams", "diane", "diapo", "dibis", "dicos", "dicte", "didot", "diene", "diese", "diete", "dieux", "diffa", "digit", "digne", "digon", "digue", "dilue", "dimes", "dinar", "dinde", "diner", "dines", "dingo", "dinka", "diode", "diola", "diols", "diots", "dires", "dirlo", "disco", "dispo", "dites", "divan", "divas", "dives", "divin", "divis", "divot", "diwan", "dixie", "dixit", "djain", "djeun", "djinn", "dobok", "dobra", "docks", "docte", "docus", "dodos", "dodue", "dodus", "dogat", "doges", "dogme", "dogon", "dogue", "doigt", "doina", "doits", "dojos", "dolby", "dolce", "dolee", "doler", "doles", "dolic", "dolly", "dolma", "dolos", "domes", "domus", "donas", "donau", "donax", "doner", "dongs", "donne", "donut", "dopee", "doper", "dopes", "doree", "dorer", "dores", "dorin", "doris", "dormi", "dosee", "doser", "doses", "dosha", "dosse", "dotal", "dotee", "doter", "dotes", "douar", "douce", "douci", "doucs", "douee", "douer", "doues", "doufe", "doula", "douma", "doums", "douro", "doute", "douve", "douze", "doxas", "doyen", "draft", "drags", "drain", "drame", "drams", "drape", "draps", "drave", "draye", "drege", "dreve", "drift", "drill", "dring", "drink", "drive", "droit", "drole", "drome", "drone", "drope", "drops", "drues", "drums", "drupe", "druse", "druze", "duale", "duals", "duaux", "ducal", "ducat", "duces", "duche", "dudit", "duels", "dugon", "duite", "duits", "dulie", "dunes", "dunks", "duodi", "dupee", "duper", "dupes", "duque", "dural", "duras", "durci", "duree", "durer", "dures", "durit", "durum", "duses", "duvet", "dyade", "dykes", "dynes", "dzeta", "eagle", "ebahi", "ebats", "ebene", "eboue", "ecale", "ecang", "ecart", "echec", "echee", "echer", "eches", "echos", "echue", "echus", "ecime", "eclat", "eclos", "ecoin", "ecole", "ecolo", "ecope", "ecote", "ecots", "ecran", "ecrie", "ecrin", "ecrit", "ecrou", "ecrue", "ecrus", "ecsta", "ecule", "ecume", "ecure", "edams", "edens", "edile", "edite", "edito", "edits", "eduen", "effet", "efrit", "egale", "egard", "egare", "egaux", "egaye", "egeen", "egide", "egout", "eider", "eject", "ejets", "eland", "elans", "elave", "elbot", "elegi", "eleis", "elemi", "eleve", "elfes", "elide", "eliee", "elier", "elies", "elime", "elire", "elise", "elite", "elles", "eloge", "eloxe", "eluat", "elude", "eluee", "eluer", "elues", "elyme", "email", "emane", "emaux", "embue", "embus", "embut", "emeri", "emeus", "emeut", "emiee", "emier", "emies", "emirs", "emise", "emois", "emoji", "emous", "empan", "empli", "emues", "emule", "emyde", "encan", "encas", "encor", "encre", "endos", "enema", "enfer", "enfeu", "enfin", "enfle", "enfui", "engin", "enjeu", "enlie", "ennui", "enols", "enoue", "entee", "enter", "entes", "entre", "envie", "envoi", "envol", "epair", "epais", "epars", "epart", "epate", "epave", "epees", "epele", "ephod", "epice", "epiee", "epier", "epies", "epieu", "epige", "epile", "epine", "epite", "epode", "epois", "epoux", "epoxy", "epris", "eprom", "epuce", "epure", "equin", "erbue", "ergol", "ergot", "erige", "erine", "erode", "errer", "erres", "erses", "esche", "escot", "esker", "espar", "essai", "esses", "essor", "ester", "estes", "estoc", "etage", "etaie", "etain", "etais", "etale", "etals", "etame", "etang", "etant", "etape", "etats", "etaux", "etaye", "etete", "eteuf", "ether", "ethos", "etier", "etige", "etire", "etocs", "etole", "etres", "etron", "etude", "etuis", "etuve", "euros", "evade", "evase", "eveil", "event", "evide", "evier", "evite", "evohe", "ewees", "exact", "exams", "exces", "exclu", "exeat", "exema", "exige", "exigu", "exile", "exils", "exine", "exits", "exode", "exons", "expat", "expie", "expos", "extra", "eyras", "fable", "faces", "fache", "facho", "facon", "fadas", "fadee", "fader", "fades", "fadet", "fados", "faena", "fagne", "fagot", "faims", "faine", "faire", "faite", "faits", "fakes", "fakir", "falle", "fallu", "falot", "falun", "famas", "famee", "fames", "fanal", "fanas", "fancy", "fanee", "faner", "fanes", "fange", "fangs", "fanny", "fanon", "fanum", "faons", "farad", "farce", "farci", "farde", "fards", "fares", "fario", "faros", "farsi", "farte", "farts", "fasce", "fassi", "faste", "fatal", "fates", "fatma", "fatum", "fatwa", "faune", "faute", "fauve", "favus", "faxee", "faxer", "faxes", "fayot", "feale", "feaux", "fecal", "feces", "fedes", "feint", "felee", "feler", "feles", "felin", "felle", "felon", "femme", "femur", "fendu", "fenil", "fente", "feral", "feras", "feria", "ferie", "ferir", "ferle", "ferme", "fermi", "ferre", "ferry", "ferte", "ferue", "ferus", "fesse", "fessu", "fetas", "fetee", "feter", "fetes", "fetus", "feues", "feuil", "feujs", "feule", "feves", "fiant", "fibre", "fibro", "ficha", "fiche", "fichu", "ficus", "fiees", "fiefs", "field", "fiels", "fiere", "fiers", "fieux", "fifis", "fifre", "figee", "figer", "figes", "figue", "filao", "filee", "filer", "files", "filet", "filin", "fille", "filme", "filmo", "films", "filon", "filos", "filou", "final", "fines", "finie", "finir", "finis", "finns", "fiole", "fions", "fiord", "fiote", "fioul", "fiqhs", "firme", "firth", "fiscs", "fissa", "fitou", "fitte", "fixee", "fixer", "fixes", "fixie", "fixin", "fjeld", "fjell", "fjord", "flags", "flair", "flanc", "flane", "flans", "flapi", "flash", "flats", "fleau", "flein", "flenu", "flets", "fleur", "flics", "flint", "flips", "flirt", "flocs", "floes", "flood", "flops", "flore", "flots", "floue", "flous", "flows", "fluer", "flues", "fluet", "fluor", "fluos", "flush", "flute", "fluxe", "flyer", "focal", "focus", "foehn", "foene", "fohne", "fohns", "foies", "foils", "foins", "foire", "folie", "folio", "folks", "folle", "fonce", "fonde", "fonds", "fondu", "fonge", "fonio", "fonte", "fonts", "foots", "force", "forci", "foree", "forer", "fores", "foret", "forge", "forme", "forte", "forts", "forum", "fossa", "fosse", "fouee", "fouet", "fouge", "fouie", "fouir", "fouis", "foule", "fours", "fouta", "foutu", "fovea", "foxee", "foxes", "foyer", "fracs", "fraie", "frais", "frake", "franc", "frape", "frase", "fraye", "freak", "frein", "frele", "fremi", "frene", "freon", "frere", "frete", "frets", "freux", "frics", "frigo", "frime", "fripe", "frire", "frise", "frita", "frite", "frits", "fritz", "frocs", "froid", "frole", "front", "froue", "fruit", "fucus", "fudge", "fuels", "fuero", "fugue", "fugus", "fuies", "fuite", "fulls", "fumat", "fumee", "fumer", "fumes", "fumet", "funes", "funin", "funks", "funky", "furax", "furet", "furia", "furie", "fusee", "fusel", "fuser", "fuses", "fusil", "fuste", "futal", "futee", "futes", "futon", "futur", "gabie", "gable", "gache", "gades", "gadin", "gadje", "gadji", "gadjo", "gaffe", "gagas", "gagee", "gager", "gages", "gagne", "gaiac", "gaies", "gaine", "gains", "gaita", "gaite", "gaize", "galas", "galbe", "gales", "galet", "galla", "galle", "gallo", "galon", "galop", "gamay", "gamba", "gambe", "gamer", "gamet", "gamin", "gamma", "gamme", "gamou", "ganga", "gangs", "ganja", "ganse", "gante", "gants", "garat", "garce", "garde", "garee", "garer", "gares", "garis", "garni", "garou", "garum", "gasba", "gaspi", "gasps", "gatee", "gater", "gates", "gatte", "gaude", "gaudi", "gaule", "gaupe", "gaura", "gaurs", "gauss", "gavee", "gaver", "gaves", "gavot", "gayal", "gazee", "gazer", "gazes", "gazon", "gazou", "geais", "geant", "gecko", "geeke", "geeks", "geint", "gelee", "geler", "geles", "gelif", "gemie", "gemir", "gemis", "gemme", "genal", "genee", "gener", "genes", "genet", "genie", "genou", "genre", "gente", "gents", "geode", "geole", "gerbe", "gerce", "geree", "gerer", "geres", "gerle", "germe", "gesir", "gesse", "geste", "ghees", "gibet", "gibus", "gicle", "gifle", "gifts", "gigas", "gigot", "gigue", "gilde", "gilet", "gille", "girie", "girls", "girly", "giron", "gitan", "gitee", "giter", "gites", "giton", "givre", "givry", "glace", "glams", "gland", "glane", "glapi", "glass", "glati", "glebe", "glene", "gleys", "glial", "glide", "glies", "globe", "glome", "glosa", "glose", "gloss", "gloup", "gluau", "gluee", "gluer", "glues", "gluis", "glume", "gluon", "gnawa", "gnete", "gnole", "gnome", "gnons", "gnose", "gnouf", "gnous", "goals", "gobee", "gober", "gobes", "gobie", "godee", "goder", "godes", "godet", "gogee", "goger", "goglu", "gogol", "gogos", "gojis", "golee", "golem", "golfe", "golfs", "golgi", "gombo", "gomme", "gonde", "gonds", "gones", "gongs", "gonio", "gonze", "gopak", "goral", "gords", "gores", "goret", "gorge", "goron", "gosse", "gotha", "gothe", "goths", "goton", "gouda", "gouet", "gouge", "goule", "goulu", "goums", "goura", "gourd", "goure", "gouro", "gours", "goute", "gouts", "goutu", "goyas", "goyim", "graal", "grace", "grade", "graff", "grafs", "grain", "grale", "grana", "grand", "graus", "graux", "grave", "gravi", "grays", "grebe", "grecs", "greee", "green", "greer", "grees", "grege", "grele", "grene", "grenu", "grese", "greve", "grief", "grill", "grils", "grime", "griot", "grips", "grise", "grive", "grogs", "groie", "groin", "grole", "groma", "groom", "group", "gruau", "grues", "gruge", "grume", "gruon", "grute", "guais", "guano", "guars", "guede", "gueee", "gueer", "guees", "guepe", "guere", "gueri", "guete", "guets", "gueux", "gueze", "gugus", "guibs", "guide", "guili", "guipe", "guise", "guppy", "gurus", "gusse", "guyot", "guzla", "gwerz", "gwoka", "gyoza", "gypse", "gyres", "gyrin", "gyros", "gyrus", "habit", "hable", "hache", "hacke", "hadal", "hadji", "hadjs", "haida", "haies", "haiks", "haiku", "haine", "haire", "hajes", "hakas", "hakka", "halal", "halbi", "halde", "halee", "haler", "hales", "halle", "halls", "halon", "halos", "halte", "halva", "hamac", "hampe", "hanap", "hands", "hanse", "hante", "hapax", "happe", "haram", "haras", "harde", "hardi", "hards", "harem", "haret", "harka", "harki", "harle", "harpe", "harts", "hasch", "hases", "haste", "hasts", "hatee", "hater", "hates", "hatif", "haute", "hauts", "havee", "haver", "haves", "havie", "havir", "havis", "havre", "hayon", "hazan", "hebdo", "hecto", "helas", "helee", "heler", "heles", "helio", "helix", "hello", "hemes", "henne", "henni", "henry", "herbe", "herbu", "heres", "heron", "heros", "herpe", "herse", "hertz", "herve", "hetre", "heure", "heurs", "heurt", "hevea", "hiant", "hibou", "hiees", "hifis", "hihan", "hijab", "hiles", "hindi", "hippo", "hippy", "hisse", "hiver", "hobby", "hocas", "hocco", "hoche", "hogan", "hoirs", "hokis", "homes", "homme", "homos", "honni", "honte", "hopak", "hopie", "hopis", "horas", "horde", "horst", "hosta", "hosto", "hosts", "hotel", "hotes", "hotte", "hotus", "houee", "houer", "houes", "houka", "houla", "houle", "hourd", "houri", "house", "hovas", "hoyau", "huant", "huard", "huart", "huche", "huees", "huhau", "huile", "humee", "humer", "humes", "humus", "hunes", "huons", "huppe", "hures", "hurle", "huron", "husky", "hutia", "hutin", "hutte", "hutue", "hutus", "hydne", "hydre", "hyene", "hymen", "hymne", "hyper", "hyphe", "hypne", "iambe", "ibere", "iboga", "iceux", "ichor", "icone", "ictus", "ideal", "ideel", "idees", "idiot", "idole", "iftar", "igame", "igbos", "igloo", "iglou", "ignee", "ignes", "igues", "ikats", "ileal", "ileon", "ilets", "ileus", "ilien", "ilion", "ilote", "ilots", "image", "imago", "imams", "imans", "imbue", "imbus", "imide", "imine", "imite", "immun", "impec", "imper", "impie", "impot", "impro", "impur", "incas", "inchs", "incus", "indes", "index", "indic", "indol", "indou", "indri", "indue", "indus", "ineat", "infos", "infox", "infra", "infus", "inies", "inlay", "innee", "innes", "innue", "innus", "inoui", "input", "insti", "inter", "intis", "intox", "intro", "inuit", "inuks", "inule", "invar", "invit", "iodee", "ioder", "iodes", "iodle", "ioule", "ipeca", "ippon", "irien", "irise", "iroko", "irone", "isard", "isbas", "islam", "ismes", "isole", "issas", "issue", "issus", "items", "itere", "ithos", "iules", "ivres", "iwans", "ixage", "ixant", "ixees", "ixias", "ixode", "jable", "jabot", "jacee", "jacks", "jacos", "jacot", "jacte", "jades", "jadis", "jaina", "jaine", "jains", "jajas", "jalap", "jales", "jalon", "jambe", "jante", "japon", "jappe", "jaque", "jarde", "jards", "jarre", "jarte", "jasee", "jaser", "jaspe", "jasse", "jatis", "jatte", "jauge", "jaune", "jauni", "javas", "javel", "jayet", "jazze", "jazzy", "jeans", "jeeps", "jello", "jenny", "jerez", "jerke", "jerks", "jeses", "jesus", "jetee", "jeter", "jetes", "jeton", "jette", "jeudi", "jeune", "jezes", "jihad", "jives", "jocko", "jodel", "jodle", "jogge", "joice", "joies", "joint", "jojos", "joker", "jolie", "jolis", "jomon", "jonce", "joncs", "joran", "jotas", "joual", "jouee", "jouer", "joues", "jouet", "jougs", "jouir", "joule", "jours", "joute", "joyau", "jubes", "juche", "judas", "judds", "judos", "judru", "jugal", "jugee", "juger", "juges", "juifs", "juins", "juive", "julep", "jules", "julie", "julot", "jumar", "jumbo", "jumel", "jumpe", "jumps", "junco", "junks", "junky", "junte", "jupes", "jupon", "jurat", "juree", "jurer", "jures", "juron", "jurys", "jusee", "juste", "juter", "jutes", "kabic", "kabig", "kabye", "kacha", "kache", "kadis", "kafir", "kagou", "kakis", "kales", "kalis", "kamis", "kanak", "kanas", "kanat", "kanji", "kaons", "kapok", "kapos", "kappa", "karen", "karma", "karst", "karts", "katas", "kavas", "kawai", "kawas", "kawis", "kayac", "kayak", "kebab", "kefie", "kefir", "kefta", "kekes", "kelps", "kemia", "kenaf", "kenas", "kendo", "kepis", "kerma", "kerns", "ketch", "ketje", "keufs", "keums", "khans", "khats", "khmer", "khobz", "khoin", "khols", "kicks", "kiefs", "kifee", "kifer", "kifes", "kiffe", "kikis", "kilim", "kilos", "kilts", "kinas", "kines", "kippa", "kitch", "kites", "kivas", "kiwis", "klaft", "knack", "knout", "koala", "koans", "kodak", "kohol", "koine", "kokas", "kolas", "kombu", "kondo", "kongo", "koppa", "koras", "kores", "koter", "kotos", "kouba", "kraal", "krach", "kraft", "kraks", "kreml", "kriek", "krill", "kriss", "ksars", "ksour", "kunas", "kurde", "kurus", "kyats", "kylix", "kyrie", "kyste", "kyudo", "labbe", "label", "labie", "labos", "labre", "labri", "lacee", "lacer", "laces", "lacet", "lache", "lacis", "lacks", "lacte", "ladin", "ladre", "ladys", "lagan", "lager", "lagon", "lahar", "laics", "laide", "laids", "laies", "laine", "laird", "laite", "laits", "laius", "laize", "lakhs", "lamas", "lamba", "lambi", "lambs", "lamee", "lamer", "lames", "lamie", "lampe", "lance", "lande", "lands", "lange", "laobe", "lapee", "laper", "lapes", "lapie", "lapin", "lapis", "lapon", "lapse", "lapsi", "laque", "larde", "lards", "lares", "large", "largo", "laris", "larix", "larme", "larve", "laser", "lasse", "lassi", "lasso", "latex", "latif", "latin", "latte", "laure", "lause", "lauze", "lavee", "laver", "laves", "lavis", "lavra", "layee", "layer", "layes", "layon", "lazes", "lazzi", "lebel", "leche", "lecon", "ledit", "legal", "legat", "leger", "leges", "legos", "legue", "lehms", "lemme", "lemur", "lente", "lento", "lents", "leone", "lepre", "lepta", "lepte", "lerch", "lerot", "lesee", "leser", "leses", "leste", "lests", "letal", "lette", "leude", "leurs", "levee", "lever", "leves", "levis", "levre", "lexie", "lexis", "liage", "liais", "liane", "liant", "liard", "liber", "libre", "lices", "liche", "licol", "licou", "lidar", "lidos", "lieds", "liees", "liege", "liens", "lieue", "lieur", "lieus", "lieux", "lifte", "lifts", "liges", "light", "ligie", "ligne", "ligot", "ligue", "likee", "liker", "likes", "lilas", "liman", "limba", "limbe", "limbo", "limee", "limer", "limes", "limon", "liner", "linga", "linge", "links", "linon", "linos", "lions", "lippe", "lippu", "lirac", "liras", "lires", "liron", "lises", "lisps", "lisse", "liste", "litas", "litee", "liter", "lites", "litho", "litra", "litre", "liure", "lives", "livet", "livre", "lloyd", "loase", "lobby", "lobee", "lober", "lobes", "lobie", "lobis", "local", "loche", "lochs", "locos", "locus", "loden", "lodge", "loess", "lofer", "lofts", "logee", "loger", "loges", "login", "logis", "logos", "logue", "loirs", "lolos", "lomos", "lompe", "lones", "longe", "longs", "lonzo", "lonzu", "looch", "loofa", "looke", "looks", "lopes", "lopin", "loque", "loran", "lords", "loris", "lorry", "loser", "loses", "lotes", "lotie", "lotir", "lotis", "lotos", "lotta", "lotte", "lotus", "louee", "louer", "loues", "loufs", "louis", "louma", "loupe", "loups", "lourd", "loure", "louve", "lovee", "lover", "loves", "loyal", "loyer", "lubie", "lucre", "lueur", "luffa", "lugee", "luger", "luges", "luire", "lulus", "lumas", "lumen", "lumes", "lumps", "lunch", "lundi", "lunee", "lunes", "lupin", "lupus", "lurex", "luron", "lusin", "lutee", "luter", "lutes", "luths", "lutin", "lutte", "luxee", "luxer", "luxes", "luzin", "lycee", "lycra", "lyoba", "lyras", "lyrer", "lyres", "lyric", "lysat", "lysee", "lyser", "lyses", "maars", "macha", "mache", "macho", "macis", "macle", "macon", "macre", "macro", "madre", "maerl", "mafes", "maffe", "mafia", "mages", "magie", "magma", "magne", "magot", "mahdi", "maias", "maies", "mails", "mains", "maint", "maire", "majes", "major", "makis", "makos", "males", "malin", "malis", "malle", "malms", "malon", "malte", "malts", "malus", "maman", "mamas", "mamba", "mambo", "mamee", "mames", "mamet", "mamie", "mamma", "mammo", "mammy", "mamys", "manas", "manat", "manda", "mande", "manes", "manga", "mange", "mango", "manie", "manif", "manip", "manne", "manon", "manou", "mansa", "manse", "manta", "mante", "manul", "maohi", "maori", "maous", "mappe", "maqam", "maque", "marae", "maras", "marcs", "mardi", "maree", "mares", "marge", "marie", "marin", "maris", "marks", "marle", "marli", "marne", "marra", "marre", "marri", "marte", "masai", "maser", "maset", "masos", "massa", "masse", "mataf", "match", "matee", "mater", "mates", "maths", "matie", "matif", "matin", "matir", "matis", "maton", "matos", "matou", "matte", "matus", "mauls", "maure", "maury", "mauve", "maxis", "mayas", "mayen", "mayes", "mayos", "mazee", "mazer", "mazes", "mazet", "mazot", "meats", "mecha", "meche", "medes", "media", "medit", "medoc", "mefie", "megas", "megie", "megir", "megis", "megot", "meiji", "melas", "melba", "melee", "meler", "meles", "melia", "meloe", "melon", "melos", "memee", "memes", "memos", "menee", "mener", "menes", "menin", "menon", "mense", "menti", "menue", "menus", "merci", "merde", "meres", "merle", "merls", "merlu", "merou", "mesas", "meson", "messe", "metal", "metas", "meteo", "metis", "metre", "metro", "meufs", "meule", "meure", "meute", "mezes", "mezig", "mezze", "mezzo", "miaou", "micas", "miche", "micro", "midis", "miels", "miens", "mieux", "migre", "mikve", "milan", "miler", "miles", "mille", "mimas", "mimee", "mimer", "mimes", "mimis", "mince", "minci", "minee", "miner", "mines", "minet", "mings", "minis", "minon", "minot", "minou", "minus", "mique", "miree", "mirer", "mires", "miros", "misee", "miser", "mises", "misos", "misse", "mitan", "mitee", "miter", "mites", "miton", "mitre", "mixee", "mixer", "mixes", "mixte", "mneme", "moais", "moche", "mocos", "modal", "modem", "modes", "modif", "moere", "mofle", "mogol", "mohos", "moine", "moins", "moire", "moise", "moisi", "moite", "moiti", "mojos", "mokas", "mokos", "moles", "molle", "molli", "mollo", "molto", "molys", "momes", "momie", "monde", "monel", "monep", "monoi", "monos", "monte", "monts", "moocs", "mooks", "moore", "moque", "moral", "morce", "mordu", "mores", "morge", "morio", "morna", "morne", "morse", "morte", "morts", "morue", "morve", "mosan", "mossi", "motel", "motet", "motif", "motos", "motte", "motus", "mouds", "moues", "moula", "moule", "moult", "moulu", "mound", "mouts", "moyee", "moyen", "moyer", "moyes", "moyeu", "muant", "muche", "mucor", "mucus", "mudra", "muees", "muets", "mufle", "mufti", "muges", "mugie", "mugir", "mugis", "muids", "mulch", "mules", "mulet", "mulla", "mulls", "mulon", "mulot", "mulud", "munda", "mungo", "munie", "munir", "munis", "muons", "mural", "muree", "murer", "mures", "muret", "murex", "murge", "murie", "murin", "murir", "muris", "murol", "muron", "muscs", "muscu", "musee", "muser", "muses", "musli", "musse", "musts", "mutee", "muter", "mutes", "mutin", "myase", "mylar", "myome", "myope", "myrte", "mythe", "mytho", "naans", "nabab", "nabis", "nabla", "nable", "nabot", "nacho", "nacre", "nadir", "naevi", "nafes", "nagas", "nagee", "nager", "nages", "nagis", "nahua", "naias", "naifs", "naine", "nains", "naira", "naive", "najas", "nakfa", "nanan", "nanar", "nanas", "nanti", "napee", "napel", "nappe", "narco", "nards", "narre", "narse", "nasal", "nases", "nashi", "nasse", "natal", "natel", "natif", "natte", "naval", "navel", "naves", "navet", "navre", "nazca", "nazes", "ndama", "ndole", "neant", "nebka", "necks", "necro", "neems", "nefle", "negus", "neige", "nells", "nemes", "nemis", "nenes", "nenni", "neons", "neper", "nepes", "nerds", "neres", "nerfs", "nervi", "nette", "neufs", "neume", "neuve", "neves", "neveu", "niais", "niant", "nibar", "nicam", "niche", "nicol", "niebe", "niece", "niees", "nieme", "niets", "nifes", "nille", "nimbe", "ninas", "ninja", "niole", "niolo", "niolu", "nippe", "niqab", "nique", "nitre", "nitro", "nival", "nives", "nixes", "nizam", "nobel", "noble", "nocer", "noces", "nocif", "nodal", "noels", "noeme", "noese", "noeud", "noire", "noirs", "noise", "nolis", "nomas", "nomes", "nomme", "nonce", "nones", "nonne", "nonos", "nopal", "norde", "nordi", "noria", "noris", "norme", "notee", "noter", "notes", "notre", "nouba", "noucs", "nouee", "nouer", "noues", "nouet", "novae", "novas", "novee", "nover", "noves", "novis", "noyat", "noyau", "noyee", "noyer", "noyes", "nuage", "nuant", "nubas", "nucal", "nuees", "nuers", "nuire", "nuits", "nulle", "nuque", "nurse", "nuton", "nyala", "nylon", "oasis", "obeie", "obeir", "obeis", "obele", "obels", "obere", "obese", "obier", "obits", "objet", "oblat", "obole", "obtus", "obvie", "occis", "ocean", "ocree", "ocrer", "ocres", "octal", "octas", "octet", "ocule", "oculi", "odeon", "odeur", "oeils", "oeufs", "oeuve", "offre", "oflag", "ogams", "ogham", "ogive", "ognon", "ogres", "oidie", "oigne", "oille", "oings", "ointe", "oints", "oisif", "oison", "okapi", "okras", "oleum", "olive", "omble", "ombre", "omega", "omise", "omras", "onces", "oncle", "ondee", "ondes", "ondin", "ongle", "onlay", "onsen", "opale", "opens", "opera", "opere", "opiat", "opine", "opium", "opter", "orage", "orale", "orant", "oraux", "orbes", "ordis", "ordos", "ordre", "orees", "orges", "orgie", "orgue", "oriel", "orins", "oriya", "orles", "orlon", "ormes", "ormet", "ornee", "orner", "ornes", "orobe", "oromo", "orpin", "orque", "ortie", "orval", "orvet", "osant", "oscar", "osees", "oside", "osier", "osmie", "osons", "osque", "ossue", "ossus", "osteo", "ostos", "otage", "otant", "otees", "otite", "otomi", "otons", "ouais", "ouate", "oubli", "ouche", "oueds", "ouest", "oufti", "ouies", "oumma", "ounce", "ourdi", "ourle", "ourse", "ouste", "outil", "outre", "ouvre", "ouzos", "ovale", "ovate", "ovees", "ovide", "ovine", "ovins", "ovnis", "ovule", "oxers", "oxime", "oxyde", "oyant", "oyats", "ozene", "ozone", "pacas", "pacha", "packs", "pacse", "pacte", "padan", "paddy", "padel", "padou", "padre", "paean", "pagee", "pagel", "pager", "pages", "pagne", "pagre", "pagus", "paien", "paies", "pains", "paire", "pairs", "pajot", "pakol", "palan", "palas", "palee", "pales", "palet", "palie", "palir", "palis", "palle", "palme", "palot", "palox", "palpe", "palud", "palus", "pamee", "pamer", "pames", "pampa", "panax", "panca", "panda", "panee", "panel", "paner", "panes", "panga", "panic", "panka", "panne", "panse", "pansu", "pante", "panty", "paons", "papal", "papas", "papes", "papet", "papis", "papou", "papys", "paque", "paras", "parce", "parcs", "pardi", "paree", "pareo", "parer", "pares", "paria", "parie", "paris", "parka", "parle", "parme", "parmi", "paroi", "paros", "parse", "parsi", "parte", "parti", "parts", "party", "parue", "parus", "paseo", "passe", "patas", "patch", "patee", "pater", "pates", "patin", "patio", "patir", "patis", "paton", "patou", "patre", "patro", "patte", "pattu", "paume", "pause", "pavee", "paver", "paves", "pavie", "pavot", "paxon", "payee", "payer", "payes", "payse", "peage", "peans", "peaux", "pecan", "peche", "pechu", "pedum", "pedze", "pegot", "pegre", "pegue", "peine", "peint", "pekan", "peket", "pekin", "pekoe", "pelee", "peler", "peles", "pelle", "pelta", "pelte", "penal", "pence", "pendu", "penes", "penil", "penis", "penne", "penny", "penon", "penos", "pense", "pente", "pentu", "penty", "peons", "pepee", "pepes", "pepie", "pepin", "pepon", "perce", "perco", "percu", "perdu", "peres", "perfo", "perfs", "perie", "perif", "peril", "perir", "perle", "perme", "perms", "perot", "perre", "perse", "perso", "perte", "pesee", "peser", "peses", "peson", "pesos", "pesse", "peste", "pesto", "petas", "petee", "peter", "petes", "petit", "peton", "petre", "petri", "pette", "petun", "peufs", "peuhl", "peule", "peuls", "peurs", "peves", "pezes", "phaco", "phage", "phare", "phase", "philo", "phlox", "phone", "phono", "photo", "phots", "phyla", "physe", "piafs", "piano", "pians", "pible", "picas", "picon", "picot", "picte", "piece", "pieds", "piege", "piers", "pieta", "piete", "pieux", "pieze", "pifee", "pifer", "pifes", "piffe", "pigee", "piger", "piges", "pigne", "pikas", "pilaf", "pilau", "pilaw", "pilee", "piler", "piles", "pilet", "pille", "pilon", "pilot", "pilou", "pilum", "pince", "pines", "pinne", "pinot", "pinta", "pinte", "pinup", "pions", "pipee", "piper", "pipes", "pipis", "pipit", "pipos", "pique", "pires", "pisan", "pisco", "pises", "pissa", "pisse", "piste", "pitas", "pitch", "pites", "pitie", "piton", "pitou", "pitre", "pitta", "pives", "pivot", "pixel", "pizza", "place", "plage", "plaid", "plaie", "plain", "plait", "plane", "plans", "plant", "plate", "plats", "plebe", "plein", "pleur", "plexi", "pliee", "plier", "plies", "plint", "plion", "plocs", "plomb", "plots", "plouc", "plouf", "plouk", "ploye", "plugs", "pluie", "pluma", "plume", "pneus", "poche", "podal", "podia", "podie", "poele", "poeme", "poete", "pogne", "pogos", "poids", "poile", "poils", "poilu", "poing", "poins", "point", "poire", "poise", "poker", "polar", "poles", "polie", "polio", "polir", "polis", "polje", "polka", "polos", "polys", "pombe", "pomme", "pompe", "ponce", "ponch", "pondu", "poney", "ponge", "ponor", "ponot", "ponte", "ponts", "pools", "popaa", "popah", "popes", "popup", "poque", "porcs", "pores", "porno", "porte", "porto", "ports", "posca", "posee", "poser", "poses", "poste", "posts", "potee", "poter", "potes", "potet", "potin", "potto", "potue", "potus", "pouah", "pouce", "pouet", "poufs", "pouic", "poule", "pouls", "pound", "poupe", "poyas", "prame", "praos", "prase", "preau", "prele", "prepa", "preta", "prete", "prets", "preux", "prevu", "priee", "prier", "pries", "prima", "prime", "primo", "prion", "prise", "prive", "proba", "probe", "procs", "prods", "profs", "proie", "projo", "prolo", "promo", "promu", "prone", "prose", "prote", "proto", "proue", "prout", "provo", "proxo", "proxy", "prude", "prune", "psitt", "psoas", "psore", "ptose", "puant", "pubis", "pucee", "pucer", "puces", "puche", "pucks", "pudus", "puees", "puine", "puise", "puits", "pujas", "pulas", "pulls", "pulpe", "pulse", "pumas", "punas", "punch", "punie", "punir", "punis", "punks", "punts", "punus", "pupes", "puree", "pures", "purge", "purin", "puros", "purot", "putes", "putte", "putti", "putto", "putts", "pyrex", "qanun", "qibla", "qings", "quado", "quads", "quais", "quand", "quant", "quark", "quart", "quasi", "qubit", "queer", "quels", "quena", "quete", "queue", "queux", "quick", "quiet", "quilt", "quine", "quint", "quipo", "quipu", "quota", "raags", "rabab", "raban", "rabat", "rabbi", "rabes", "rabla", "rable", "rabot", "racee", "racer", "races", "rachi", "racho", "racks", "racle", "radar", "radee", "rader", "rades", "radia", "radie", "radin", "radio", "radis", "radja", "radon", "rafle", "rafts", "ragas", "rager", "rages", "ragga", "ragot", "rague", "raias", "raide", "raidi", "raids", "raies", "rails", "raine", "raire", "raita", "rajah", "rajas", "rakis", "rakus", "raler", "rales", "ralle", "ramas", "ramat", "ramee", "ramen", "ramer", "rames", "ramie", "ramin", "ramis", "rampe", "rance", "ranch", "ranci", "rando", "rands", "range", "rangs", "ranis", "raout", "rapee", "raper", "rapes", "raphe", "rapia", "rapin", "rappe", "rapts", "raque", "rares", "rasas", "rasee", "raser", "rases", "rashs", "rassi", "rasta", "ratee", "ratel", "rater", "rates", "ratio", "raton", "ratte", "raval", "raver", "raves", "ravie", "ravin", "ravir", "ravis", "rayas", "rayee", "rayer", "rayes", "rayia", "rayon", "rbati", "reacs", "reagi", "reais", "reale", "reals", "reant", "reaux", "rebab", "rebat", "rebec", "rebeu", "rebot", "rebue", "rebus", "rebut", "recap", "recel", "reces", "recez", "reche", "recif", "recit", "recks", "recre", "recru", "recta", "recto", "recue", "recul", "recup", "recus", "redac", "redan", "redie", "redif", "redit", "redon", "redox", "reduc", "redue", "redus", "reels", "reelu", "refus", "regal", "regel", "regie", "regir", "regis", "regle", "reglo", "regne", "regur", "reiki", "reine", "reins", "rejet", "relai", "relax", "relie", "relou", "relue", "relui", "relus", "remis", "remix", "remiz", "remue", "renal", "rende", "rendu", "renee", "renes", "renie", "renne", "renom", "renon", "rente", "repas", "repic", "repit", "repli", "replu", "repos", "repro", "repue", "repus", "resas", "resta", "reste", "resto", "retif", "retro", "reuni", "revee", "rever", "reves", "revif", "revue", "revus", "rheme", "rheto", "rhino", "rhodo", "rhumb", "rhume", "rhums", "riads", "rials", "riant", "ribat", "rible", "ribot", "riche", "richi", "ricin", "ridee", "rider", "rides", "riels", "riens", "rieur", "riffe", "riffs", "rifle", "rifts", "rikio", "rimee", "rimer", "rimes", "rince", "rings", "rioja", "riote", "ripee", "riper", "ripes", "ripou", "rires", "risee", "riser", "rishi", "risse", "riste", "rital", "rites", "rival", "rivee", "river", "rives", "rivet", "rixes", "riyal", "robee", "rober", "robes", "robin", "robot", "robre", "roche", "rocks", "rocou", "rodee", "rodeo", "roder", "rodes", "rodez", "rogne", "rogue", "roide", "roidi", "rokhs", "roles", "rolle", "rolls", "roman", "rompu", "ronce", "ronde", "rondi", "rondo", "ronds", "roneo", "ronge", "ronin", "roofs", "roque", "rosat", "rosee", "roser", "roses", "rosie", "rosir", "rosis", "rosse", "rosti", "rotas", "rotee", "roter", "rotes", "rotie", "rotin", "rotir", "rotis", "rotor", "rotos", "rouan", "rouee", "rouer", "roues", "rouet", "roufs", "rouge", "rough", "rougi", "rouie", "rouir", "rouis", "roule", "roumi", "round", "route", "rover", "royal", "ruade", "ruant", "ruban", "rubis", "ruche", "rucks", "rudes", "ruees", "rugby", "rugie", "rugir", "rugis", "ruile", "ruine", "rully", "rumba", "rumbs", "rumen", "rumex", "runes", "ruolz", "rupee", "ruper", "rupes", "rupin", "rural", "rusee", "ruser", "ruses", "rushs", "russe", "ryads", "ryals", "saami", "sabar", "sabin", "sabir", "sable", "sabot", "sabra", "sabre", "sache", "sacre", "sacys", "sadhu", "sados", "safou", "safre", "sagas", "sages", "sagou", "sagum", "sahel", "sahib", "saies", "saiga", "saine", "sains", "saint", "saisi", "saite", "sajou", "sakes", "sakis", "sakti", "salam", "salar", "salat", "salee", "salep", "saler", "sales", "salie", "salin", "salir", "salis", "salle", "salol", "salon", "salop", "salpe", "salsa", "salse", "salto", "salue", "salut", "salve", "samba", "sambo", "sames", "samie", "samis", "samit", "sammy", "samos", "sampi", "samus", "sanas", "sango", "sangs", "sanie", "sante", "sanve", "sanza", "saola", "saoul", "sapee", "saper", "sapes", "sapin", "saque", "saras", "sarde", "sarin", "saris", "sarod", "saron", "saros", "sarts", "sassa", "sasse", "satan", "satay", "sates", "satin", "satis", "sauce", "saufs", "sauge", "saule", "sauna", "saune", "saupe", "saure", "sauri", "saurs", "saute", "sauts", "sauve", "savon", "saxes", "saxon", "saxos", "sayon", "sbire", "scalp", "scans", "scare", "scato", "scats", "sceau", "scene", "schah", "schwa", "sciee", "scier", "scies", "scion", "scone", "scoop", "scoot", "scopa", "scope", "score", "scout", "scrub", "scuds", "scull", "scuta", "seant", "seaux", "sebka", "sebum", "secam", "secco", "seche", "secte", "secus", "sedan", "sedon", "sedum", "segas", "seide", "seime", "seine", "seing", "seins", "seize", "selfs", "selle", "selon", "seltz", "selva", "selve", "semai", "semee", "semer", "semes", "semis", "senat", "senau", "senes", "senne", "sensa", "sense", "sente", "senti", "seoir", "sepia", "serac", "seran", "serbe", "seres", "serfs", "serge", "serie", "serin", "serpe", "serre", "serte", "serti", "serum", "serve", "servi", "setar", "seton", "seuil", "seule", "seuls", "seums", "seves", "sevir", "sevre", "sexee", "sexer", "sexes", "sexte", "sexto", "sexue", "sexys", "sezig", "shahs", "shako", "shama", "shana", "shans", "sheds", "shelf", "sheol", "shiba", "shido", "shift", "shire", "shits", "shogi", "shona", "shoot", "short", "shots", "shows", "shoyu", "shunt", "sials", "sicav", "sicle", "sidas", "sidis", "siege", "siens", "sieur", "sigle", "sigma", "signe", "sikhe", "sikhs", "silat", "siler", "silex", "silos", "silts", "simas", "singe", "sinoc", "sinon", "sinue", "sinus", "sioux", "sipos", "sires", "sirex", "sirli", "sirop", "sisal", "sises", "sitar", "sites", "sitot", "situe", "siums", "sixte", "skais", "skate", "skats", "skeet", "skiee", "skier", "skies", "skiff", "skifs", "skins", "skips", "skons", "skuas", "skuns", "slame", "slams", "slang", "slash", "slave", "slice", "slide", "slims", "slips", "sloop", "slows", "slums", "slurp", "slush", "smack", "smala", "smalt", "smart", "smash", "smics", "smogs", "smoks", "smolt", "smurf", "snack", "snife", "sniff", "snifs", "snobe", "snobs", "soaps", "sobre", "socca", "socio", "socle", "sodas", "sodee", "sodes", "soeur", "sofas", "softs", "soies", "soifs", "soins", "soirs", "sojas", "solde", "solea", "solen", "soles", "solex", "solin", "solos", "soman", "somas", "sombe", "somme", "sonal", "sonar", "sonde", "sones", "songe", "songs", "sonie", "sonna", "sonne", "sonos", "sopor", "sorbe", "sores", "sorgo", "sorte", "sorti", "sorts", "sosie", "sosot", "sotch", "sotho", "sotie", "sotte", "souci", "soude", "soues", "soufi", "souks", "soule", "souls", "soums", "souna", "soupe", "sourd", "souri", "soute", "soyas", "soyer", "space", "spahi", "spams", "spare", "spart", "spath", "spats", "speck", "speed", "speos", "spets", "sphex", "spica", "spics", "spins", "spire", "spita", "spite", "spitz", "spore", "sport", "spots", "sprat", "spray", "sprue", "spume", "squat", "squaw", "stade", "staff", "stage", "stamm", "stand", "stars", "stase", "stats", "steak", "stele", "stemm", "stems", "steno", "stent", "steps", "stere", "stick", "stilb", "stipe", "stock", "stone", "stops", "store", "stots", "stout", "stras", "strie", "strip", "strix", "stucs", "studs", "stuka", "stupa", "stups", "stuut", "style", "stylo", "suage", "suant", "suave", "suber", "subie", "subir", "subis", "subit", "suble", "sucee", "sucer", "suces", "sucon", "sucre", "sudra", "suede", "suees", "sueur", "sueve", "suffi", "sufis", "suide", "suies", "suife", "suifs", "suint", "suite", "suive", "suivi", "sujet", "sulky", "sumac", "sumos", "sunna", "supee", "super", "supes", "supin", "suppo", "supra", "surah", "sural", "sures", "suret", "surfe", "surfs", "surge", "surgi", "surie", "surin", "surir", "suris", "suros", "sushi", "sutra", "swags", "swaps", "swazi", "sweat", "swing", "swins", "sylis", "sylve", "sympa", "syrah", "syrte", "taals", "tabac", "tabar", "tabes", "tabla", "table", "tabor", "tabou", "tabun", "tacca", "tacet", "tache", "tacks", "tacle", "tacon", "tacos", "tacot", "tacts", "taels", "taffe", "tafia", "tagal", "tagge", "tagme", "tagua", "tague", "tahrs", "taies", "taiga", "taiji", "taino", "tains", "taire", "takas", "takin", "talas", "talcs", "taleb", "taled", "talee", "taler", "tales", "talet", "talle", "talon", "talus", "tamas", "tamia", "tamil", "tamis", "tance", "tanga", "tango", "tangs", "tanin", "tanka", "tanks", "tanne", "tanns", "tante", "taons", "tapas", "tapee", "taper", "tapes", "tapie", "tapin", "tapir", "tapis", "tapon", "taque", "taraf", "tarde", "taree", "tarer", "tares", "taret", "targe", "tarie", "tarif", "tarin", "tarir", "taris", "taros", "tarot", "tarse", "tarte", "tarti", "taser", "tassa", "tasse", "tatar", "tatas", "tatee", "tater", "tates", "tatie", "tatin", "tatis", "tatou", "taude", "tauds", "taule", "tauon", "taupe", "taure", "tavel", "taxee", "taxer", "taxes", "taxie", "taxis", "taxol", "taxon", "taxum", "taxus", "tayra", "tchan", "tchao", "tchat", "tchin", "teams", "tecks", "teddy", "tefal", "teffs", "teint", "tejus", "tekee", "tekes", "teles", "telex", "telle", "tells", "tempe", "tempi", "tempo", "temps", "tende", "tendu", "tenge", "tenia", "tenir", "tenno", "tenon", "tenor", "tente", "tenue", "tenus", "tepui", "terce", "terme", "terne", "terni", "terre", "terri", "terse", "tesla", "testa", "teste", "tests", "tetee", "teter", "tetes", "tetin", "teton", "tetra", "tette", "tetue", "tetus", "teufs", "teves", "texan", "texte", "texto", "tezig", "thaie", "thais", "thali", "thane", "theme", "these", "theta", "thete", "thiof", "thiol", "thons", "thora", "thugs", "thune", "thuya", "thyms", "tians", "tiare", "tibia", "tical", "tiede", "tiedi", "tiens", "tiers", "tiffe", "tifos", "tiger", "tiges", "tigre", "tikis", "tilde", "tilla", "tille", "tilte", "tilts", "timon", "tines", "tinte", "tipee", "tiper", "tipes", "tipis", "tippe", "tique", "tiree", "tirer", "tires", "tiret", "tiser", "tises", "tison", "tisse", "tissu", "titan", "titis", "titre", "titus", "tjale", "tmese", "toast", "tobys", "tofus", "toges", "toile", "toise", "toits", "tokai", "tokaj", "tokay", "tolar", "tolba", "tolee", "toler", "toles", "tolet", "tolle", "tolus", "toman", "tombe", "tomee", "tomer", "tomes", "tomme", "tommy", "tonal", "tonca", "tondo", "tondu", "toner", "tonfa", "tongs", "tonic", "tonie", "tonka", "tonne", "tonte", "tonus", "topee", "toper", "topes", "topic", "topos", "toque", "torah", "tordu", "toree", "tores", "torii", "toril", "toron", "torrs", "torse", "torte", "torts", "tortu", "torve", "torys", "tosas", "tosse", "total", "totem", "toton", "totos", "touee", "touer", "toues", "toura", "tourd", "toure", "tours", "toute", "touts", "trabe", "trace", "tracs", "tract", "trahi", "traie", "trail", "train", "trait", "trame", "tramp", "trams", "trans", "trapp", "trapu", "trash", "treks", "trema", "trend", "treve", "trial", "trias", "tribu", "trick", "trics", "tridi", "triee", "trier", "tries", "trigo", "trike", "trime", "trine", "trins", "triol", "trios", "tripe", "trips", "trocs", "trois", "trole", "troll", "trona", "tronc", "trone", "trope", "trots", "troue", "trous", "truck", "trucs", "truie", "trust", "tsars", "tsuba", "tsuga", "ttoro", "tuage", "tuant", "tubas", "tubee", "tuber", "tubes", "tuees", "tueur", "tufte", "tuile", "tulle", "tumba", "tunee", "tuner", "tunes", "tupie", "tupis", "tuque", "turbe", "turbo", "turco", "turcs", "turfs", "turne", "tutie", "tutos", "tutsi", "tutti", "tutus", "tuyau", "tweed", "tween", "tweet", "twill", "twins", "twist", "typee", "typer", "types", "typha", "typon", "typos", "tyran", "tzars", "ubacs", "ubris", "ugnis", "uhlan", "ukase", "ulema", "ulnas", "ultra", "ulule", "ulves", "umami", "umbos", "ummas", "unaus", "unaux", "unies", "unifs", "union", "unite", "univs", "untel", "urane", "urate", "urdus", "urees", "urger", "urine", "urnes", "ursin", "urubu", "usage", "usant", "usees", "usine", "usite", "usnee", "usuel", "usure", "utile", "uvale", "uvaux", "uvees", "uvula", "uvule", "uzbek", "vache", "vacoa", "vagal", "vagin", "vagir", "vague", "vaine", "vains", "vaire", "vairs", "valet", "valga", "valse", "value", "valus", "valve", "vampe", "vamps", "vanda", "vanne", "vante", "vapes", "vapos", "vaque", "varan", "varia", "varie", "varna", "varon", "varus", "varve", "vasee", "vaser", "vases", "vaste", "vatus", "veaux", "veces", "vecue", "vecus", "vedas", "vegan", "veine", "velar", "velas", "velds", "veldt", "veler", "veles", "velet", "velie", "velin", "velle", "velos", "velot", "velte", "velue", "velum", "velus", "velux", "venal", "venda", "vendu", "venes", "venet", "venge", "venin", "venir", "venta", "vente", "vents", "venue", "venus", "verbe", "verdi", "verge", "verif", "verin", "verne", "verni", "verre", "verse", "verso", "verte", "verts", "vertu", "verve", "vesce", "vesou", "vespa", "vesse", "veste", "vetir", "vetos", "vetue", "vetus", "veufs", "veule", "veuve", "vexee", "vexer", "vexes", "vibor", "vibre", "vibro", "vices", "vichy", "vicie", "videe", "video", "vider", "vides", "vieil", "viele", "viets", "vieux", "vigie", "vigil", "vigne", "viles", "villa", "ville", "vimes", "vinas", "vinee", "viner", "vines", "vingt", "vinyl", "viocs", "viola", "viole", "viols", "viral", "viree", "vireo", "virer", "vires", "viril", "virus", "visas", "visee", "viser", "vises", "vison", "visou", "visse", "vista", "vital", "vites", "vitre", "vivat", "vives", "vivre", "vizir", "vlogs", "vocal", "vodka", "voeux", "vogue", "voici", "voies", "voila", "voile", "voire", "voise", "volee", "voler", "voles", "volet", "volis", "volte", "volts", "volve", "vomer", "vomie", "vomir", "vomis", "votee", "voter", "votes", "votif", "votre", "vouee", "vouer", "voues", "vouge", "voulu", "voute", "voyer", "voyou", "vracs", "vraie", "vrais", "vroom", "vroum", "vulgo", "vulve", "wagon", "wales", "walis", "waouh", "waqfs", "wasps", "watte", "watts", "weber", "wedge", "welsh", "wenge", "wenze", "wharf", "whigs", "whips", "whist", "widia", "wifis", "wikis", "wimax", "winch", "wiski", "wolof", "wraps", "wurms", "wushu", "xalam", "xenon", "xeres", "xerus", "xhosa", "xiang", "xieme", "xipho", "xylol", "xyste", "yacht", "yacks", "yakas", "yamba", "yangs", "yapok", "yards", "yassa", "yasse", "yawls", "yeble", "yetis", "yeuse", "yeyes", "yodel", "yodle", "yogas", "yogis", "yoles", "yorks", "youpi", "yoyos", "yuans", "yucca", "yukos", "yuzus", "zabre", "zains", "zaire", "zakat", "zamak", "zamia", "zamus", "zanis", "zanni", "zanzi", "zappe", "zarbi", "zarbs", "zarma", "zazen", "zazou", "zebre", "zebus", "zeine", "zelee", "zeles", "zende", "zends", "zeros", "zeste", "zigue", "zikrs", "zincs", "zippe", "zizis", "zloty", "zoide", "zoile", "zombi", "zonal", "zonas", "zonee", "zoner", "zones", "zoome", "zooms", "zorse", "zouke", "zouks", "zozos", "zumba"]

WORD_LIST = WORD_LIST.concat(SOLUTION_LIST);    //combine les 2 tab WORDLIST et SOLLIST

var mot=SOLUTION_LIST[Math.floor(Math.random()*SOLUTION_LIST.length)];  //genere un mot aleatoire

console.log(mot);

//quand la page se charge
window.onload = function() 
{
    recuperProgressWordle();              //recuperer les progres depuis la bdd
    initialiser();                        // initialise le jeu au chargement de la page
}

function afficherScore() {
    document.getElementById('scoreActuel').textContent = scoreActuel;
}

function afficherNiveau() {
    document.getElementById('niveauActuel').textContent = niveauActuel;
}

function initialiser() 
{
    
    //rajouter les lettres dans le plateau
    for(let i=0; i<lig; i++)
    {
        for(let j=0; j<col; j++)
        {
            //Case est un element de plateau 
            let Case=document.createElement("span");   //<span id="0-0" class="case> </span>
            Case.id=i.toString() + "-" + j.toString(); 
            Case.classList.add("Case");
            Case.innerText="";
            document.getElementById("plateau").appendChild(Case);
        }
    }

    let clavier=[
        ["a", "z", "e", "r", "t", "y", "u", "i", "o", "p"],
        ["q", "s", "d", "f", "g", "h", "j", "k", "l", "m"],
        ["Entrer", "w", "x", "c", "v", "b", "n", "⌫"]
    ]

    //cree le clavier
    for(let r=0;r<clavier.length;r++)       
    {
        let ligneCourante=clavier[r];
        let ligneClavier=document.createElement("div");
        ligneClavier.classList.add("ligneClavier");

        for(let l=0;l<ligneCourante.length;l++)
        {
            let toucheClavier =document.createElement("div");
            let touche=ligneCourante[l];
            toucheClavier.innerText = touche;

            if(touche == "Entrer")
            {
                toucheClavier.id="Enter";
            }
            else if(touche == "⌫")
            {
                toucheClavier.id="Backspace";
            }
            else if ("a"<=touche && touche<="z")
            {
                toucheClavier.id = touche;
            }

            toucheClavier.addEventListener("click",gestionTouche);  //clique souris

            if(touche =="Entrer" )
            {
                toucheClavier.classList.add("toucheAutreClavier");
            }
            if(touche =="⌫" )
            {
                toucheClavier.classList.add("toucheAutreClavier");
            }
            else
            {
                toucheClavier.classList.add("toucheClavier");
            }

            ligneClavier.appendChild(toucheClavier);

        }
        document.body.appendChild(ligneClavier);
    }

    //touche clavier relacher
    document.addEventListener("keyup", (event) => {
        gestionEntree(event);
    })
}

function gestionTouche()
{
    let event= {"key": this.id};
    gestionEntree(event);
}

function gestionEntree(event)
{
    if(finJeu==true)
    {
        return;
    }

    let lettre = event.key;
    
    if ("a" <= lettre && lettre <= "z") 
    {
        if(posCol<col)  //verifie si depasse pas le tableau
        {
            let caseCourante = document.getElementById(posLig.toString() + "-" + posCol.toString() );
            if (caseCourante.innerText=="") // si vide
            {
                caseCourante.innerText=lettre; //recupere-affiche la lettre entree
                posCol+=1;//ajout lettre
            }
        }
    }
    else if(lettre =="Backspace" )
    {
        if(0<posCol && posCol<=col) //verifie si depasse pas le tableau
        {
            posCol-=1; //on recule
        }
        let caseCourante = document.getElementById(posLig.toString() + "-" + posCol.toString() );
        caseCourante.innerText=""; //case vider

    }
    else if(lettre == "Enter")
    {
        maj();
    }

    if(!finJeu && posLig == lig )       //si perdu
    {
        finJeu=true;
        document.getElementById("reponse").innerText="Perdu 😞... le mot a trouvé était  "+mot;   //affiche donc le mot a trouver 
        document.getElementById("btnRejouer").style.display = 'block';
        document.getElementById("btnIndice").style.display = 'none';
        saveProgressWordle(niveauActuel, scoreActuel); 
    }
}

function maj()
{
    let motEntree="";
    document.getElementById("reponse").innerText="";
    let correct =0;
    let nblettre={};


    for(let h=0; h<col;h++)       // remplie la ligne de lettre
    {
        let caseCourante=document.getElementById(posLig.toString() + "-" + h.toString()); 
        let lettreEntree= caseCourante.innerText;
        motEntree+=lettreEntree;        // motEntree est composé des lettres entrees 
    }

    if(!WORD_LIST.includes(motEntree) )       // si le mot entree ne se trouve pas dans la liste des mots quon peut entree
    {
        document.getElementById("reponse").innerText="Ce mot n'est pas dans la liste";      //alors affiche msg
        return;
    }

    for(let j=0;j<mot.length;j++)
    {
        let lettreEntree=mot[j];        // mot est le mot a deviner
        if(nblettre[lettreEntree])      //verifie  le nombre d'occurence de lettres dans le mot ex: mot=femme 1xf 2xe 2xm
        {
            nblettre[lettreEntree]+=1;
        }
        else
        {
            nblettre[lettreEntree]=1;
        }
    }

    //rechercher lettre correct et bien placee
    for(let i=0; i<col; i++)
    {
        let caseCourante = document.getElementById(posLig.toString() + "-" + i.toString() );
        let lettreEntree= caseCourante.innerText;

        if(mot[i] == lettreEntree)   //si lettre correct et bien placee
        {                 
            caseCourante.classList.add("correcte");

            let toucheClavier=document.getElementById(lettreEntree);
            toucheClavier.classList.remove("malplacee");
            toucheClavier.classList.add("correcte");
            
            correct+=1;                     //compte nombre de lettres entrees correctes
            nblettre[lettreEntree]-=1;      //diminue le nombre de lettres correct tel que "balle": 1b 1a 2l 1e =>1b 0a 1l 1e si on a entree "l" et "a"
        }

        if(correct == col)          //si nombre de toutes les lettres entrees sont correctes et bien place donc 5
        {
            finJeu=true;            //alors fin du jeu 
    
            document.getElementById("reponse").innerText="Bravo 👏! Tu as gagné !";
            document.getElementById("btnRejouer").style.display = 'block';
            document.getElementById("btnIndice").style.display = 'none';
            
            scoreActuel += 10;  // rajoute 10 points pour partie gagnee
            afficherScore(); 

            niveauActuel ++;  // increment le niveau
            afficherNiveau(); 

            saveProgressWordle(niveauActuel, scoreActuel); // sauvegarde des donnees (score et niveau)
        }
    
    }

    //rechercher  lettre correct et mal placee
    for(let i=0; i<col; i++)
    {
        let caseCourante = document.getElementById(posLig.toString() + "-" + i.toString() );
        let lettreEntree= caseCourante.innerText;

        if(!caseCourante.classList.contains("correcte")) // si la case n'est pas verte
        {
            if( mot.includes(lettreEntree) && nblettre[lettreEntree]>0)           //si lettre correct et mal placee
            {
                caseCourante.classList.add("malplacee");
                let toucheClavier=document.getElementById(lettreEntree);

                if(!toucheClavier.classList.contains("correcte")) 
                {
                    toucheClavier.classList.add("malplacee");
                }

                nblettre[lettreEntree]-=1;  
            }
            else 
            {
                caseCourante.classList.add("incorrecte");
                let toucheClavier=document.getElementById(lettreEntree);
                if(!toucheClavier.classList.contains("correcte") && !toucheClavier.classList.contains("malplacee"))  
                {
                    toucheClavier.classList.add("incorrecte");
                }
            }
        }
    }

    //maj des positions 
    posLig+=1; //ajout ligne
    posCol=0;   //debut ajout lettre

}

function rejouer() {

    document.location.reload(); //recharge la page
    clearInterval(interval);    //arrete tout execution 
    
}

function acheterIndice() {
    
    if (indiceUtilise) {
        
        alert("Vous avez déjà utilisé votre indice pour cette partie!");
        return;
    }
    
    if (scoreActuel >= 50)  // verifie si l'user a au moins 50 pts
    {
        scoreActuel -= 50; // on deduit 50 pts
        afficherScore();
        revelerIndice();
        indiceUtilise = true; //indice utilise
    
    } 
    else 
    {
        alert("Pas assez de points pour un indice!");
    }
}

function revelerIndice() 
{
    let indiceRevele = false;

    for (let i = 0; i < mot.length; i++) {
        let lettreDejaTrouvee = false;

        for (let j = 0; j < posLig; j++) {
            let caseCourante = document.getElementById(j.toString() + "-" + i.toString());
            if (caseCourante.classList.contains("correcte") || caseCourante.innerText === mot[i]) {
                lettreDejaTrouvee = true;
                break;
            }
        }

       //si lettre pas encore trouver 
        if (!lettreDejaTrouvee && !document.getElementById(mot[i]).classList.contains("correcte")) {
            let toucheClavier = document.getElementById(mot[i]); 
            if (toucheClavier) {
                toucheClavier.classList.add("malplacee"); 
                indiceRevele = true;
            }
        }
    }

    if (!indiceRevele) {
        alert("Aucun nouvel indice disponible pour le moment.");
    }
}


function saveProgressWordle(niveauActuel, scoreActuel)
{

    $.ajax({
        url: './../Controleur/saveProgressWordle.php',

        type: 'POST',
        
        data: 
        {
            'scoreActuel': scoreActuel,
            'niveauActuel': niveauActuel
        },
        
        success: (data) => {
            let response = JSON.parse(data);
            if (response.code === 200) 
                console.log('Réponse du serveur (save):', response);
        },

        error: (jqXHR, status, erreur) => {
            console.error('Erreur lors de la sauvegarde :', erreur);
            console.error('Statut de la requête :', status);
            console.error('Réponse du serveur :', jqXHR.responseText);
        }
    });
}



function recuperProgressWordle() 
{

    $.ajax(
    {
        url: './../Controleur/recupererDataWordle.php',

        type: 'GET',

        dataType: 'json',

        success: function(response) 
        {
            console.log('Réponse du serveur (recup):', response);
            if (response.status === 'success' && response.data.length > 0) 
            {
                niveauActuel = response.data[0].level;
                scoreActuel = response.data[0].points;

                afficherScore();
                afficherNiveau();

            } 
            else 
            {
                console.error('Erreur lors de la récupération des données: ', response.message);
            }
        },
        error: function(xhr, status, error) 
        {
            console.error('Erreur lors de la communication avec le serveur:', error);
        }
    });
}

