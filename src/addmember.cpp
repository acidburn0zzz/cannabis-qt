#include "addmember.h"

AddMember::AddMember(QWidget *parent) :
    QDialog(parent)
{
    model = NULL;

    /*
     codi soci
     data alta
     dni
     nom
     primer cognom
     segon cognom
     adreça
     telefon
     codi postal
     població
     e-mail
     pagat
     */


    QLineEdit *codiLineEdit = new QLineEdit;

    QDateEdit *altaDateEdit = new QDateEdit;
    altaDateEdit->setDate(QDate::currentDate());
    altaDateEdit->setDisplayFormat("dd/MM/yyyy");
    altaDateEdit->setCalendarPopup(true);

    QLineEdit *dniLineEdit = new QLineEdit;
    QLineEdit *nomLineEdit = new QLineEdit;
    QLineEdit *primerCognomLineEdit = new QLineEdit;
    QLineEdit *segonCognomLineEdit = new QLineEdit;
    QLineEdit *addrLineEdit = new QLineEdit;
    QLineEdit *tlfLineEdit = new QLineEdit;
    QLineEdit *cpLineEdit = new QLineEdit;
    QComboBox *municipiComboBox = new QComboBox;
    QComboBox *comarcaComboBox = new QComboBox;
    QLineEdit *emailLineEdit = new QLineEdit;
    QCheckBox *pagatCheckBox = new QCheckBox;

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Close);

    QFormLayout *layout = new QFormLayout;

    layout->addRow(tr("Codi:"), codiLineEdit);
    layout->addRow(tr("Alta:"), altaDateEdit);
    layout->addRow(tr("DNI:"), dniLineEdit);
    layout->addRow(tr("Nom:"), nomLineEdit);
    layout->addRow(tr("Primer Cognom:"), primerCognomLineEdit);
    layout->addRow(tr("Segon Cognom:"), segonCognomLineEdit);
    layout->addRow(tr("Adreça:"), addrLineEdit);
    layout->addRow(tr("Telèfon:"), tlfLineEdit);
    layout->addRow(tr("Codi Postal:"), cpLineEdit);
    layout->addRow(tr("Municipi:"), municipiComboBox);
    layout->addRow(tr("Comarca:"), comarcaComboBox);
    layout->addRow(tr("E-mail:"), emailLineEdit);
    layout->addRow(tr("Pagat:"), pagatCheckBox);

    layout->addRow(buttonBox);

    setLayout(layout);
}

void AddMember::setModel(QSqlTableModel *model)
{
    this->model = model;
}

/*
Abella de la Conca	Pallars Jussà
Abrera	Baix Llobregat	11611
Àger	Noguera	590
Agramunt	Urgell	5653
Aguilar de Segarra	Bages	245
Agullana	Alt Empordà	839
Aiguafreda	Vallès Oriental	2481
Aiguamúrcia	Alt Camp	917
Aiguaviva	Gironès	754
Aitona	Segrià	2405
Els Alamús	Segrià	748
Alàs i Cerc	Alt Urgell	366
L'Albagés	Garrigues	449
Albanyà	Alt Empordà	150
Albatàrrec	Segrià	2040
Albesa	Noguera	1656
L'Albi	Garrigues	860
Albinyana	Baix Penedès	2347
L'Albiol	Baix Camp	451
Albons	Baix Empordà	709
Alcanar	Montsià	10601
Alcanó	Segrià	233
Alcarràs	Segrià	8350
Alcoletge	Segrià	3015
Alcover	Alt Camp	5140
L'Aldea	Baix Ebre	4513
Aldover	Baix Ebre	978
L'Aleixar	Baix Camp	914
Alella	Maresme	9570
Alfara de Carles	Baix Ebre	400
Alfarràs	Segrià	3107
Alfés	Segrià	331
Alforja	Baix Camp	1866
Algerri	Noguera	450
Alguaire	Segrià	3097
Alins	Pallars Sobirà	305
Alió	Alt Camp	380
Almacelles	Segrià	6662
Almatret	Segrià	378
Almenar	Segrià	3605
Almoster	Baix Camp	1362
Alòs de Balaguer	Noguera	138
Alp	Cerdanya	1743
Alpens	Osona	302
Alpicat	Segrià	6190
Alt Àneu	Pallars Sobirà	450
Altafulla	Tarragonès	4776
Amer	Selva	2277
L'Ametlla de Mar	Baix Ebre	7649
L'Ametlla del Vallès	Vallès Oriental	8111
L'Ampolla	Baix Ebre	3529
Amposta	Montsià	21445
Anglès	Selva	5637
Anglesola	Urgell	1389
Arbeca	Garrigues	2493
L'Arboç	Baix Penedès	5548
Arbolí	Baix Camp	114
Arbúcies	Selva	6713
Arenys de Mar	Maresme	14863
Arenys de Munt	Maresme	8500
Argelaguer	Garrotxa	424
Argençola	Anoia	238
L'Argentera	Baix Camp	159
Argentona	Maresme	11776
L'Armentera	Alt Empordà	863
Arnes	Terra Alta	496
Arres	Val d'Aran	64
Arsèguel	Alt Urgell	100
Artés	Bages	5575
Artesa de Lleida	Segrià	1524
Artesa de Segre	Noguera	3828
Ascó	Ribera d'Ebre	1665
Aspa	Segrià	224
Les Avellanes i Santa Linya	Noguera	470
Avià	Berguedà	2245
Avinyó	Bages	2321
Avinyonet de Puigventós	Alt Empordà	1509
Avinyonet del Penedès	Alt Penedès	1710
Badalona	Barcelonès	219786
Badia del Vallès	Vallès Occidental	13643
Bagà	Berguedà	2372
Baix Pallars	Pallars Sobirà	382
Balaguer	Noguera	16877
Balenyà	Osona	3695
Balsareny	Bages	3494
Banyeres del Penedès	Baix Penedès	2995
Banyoles	Pla de l'Estany	19159
Barbens	Pla d'Urgell	896
Barberà de la Conca	Conca de Barberà	540
Barberà del Vallès	Vallès Occidental	32033
Barcelona	Barcelonès	1615448
La Baronia de Rialb	Noguera	257
Bàscara	Alt Empordà	985
Bassella	Alt Urgell	255
Batea	Terra Alta	2150
Bausen	Val d'Aran	59
Begues	Baix Llobregat	6426
Begur	Baix Empordà	4219
Belianes	Urgell	578
Bellaguarda	Garrigues	325
Bellcaire d'Empordà	Baix Empordà	664
Bellcaire d'Urgell	Noguera	1356
Bell-lloc d'Urgell	Pla d'Urgell	2446
Bellmunt del Priorat	Priorat	337
Bellmunt d'Urgell	Noguera	202
Bellprat	Anoia	91
Bellpuig	Urgell	5000
Bellvei	Baix Penedès	2082
Bellver de Cerdanya	Cerdanya	2260
Bellvís	Pla d'Urgell	2404
Benavent de Segrià	Segrià	1553
Benifallet	Baix Ebre	803
Benissanet	Ribera d'Ebre	1249
Berga	Berguedà	17018
Besalú	Garrotxa	2372
Bescanó	Gironès	4601
Beuda	Garrotxa	170
Bigues i Riells	Vallès Oriental	8755
Biosca	Segarra	222
La Bisbal de Falset	Priorat	225
La Bisbal del Penedès	Baix Penedès	3373
La Bisbal d'Empordà	Baix Empordà	10435
Biure	Alt Empordà	248
Blancafort	Conca de Barberà	415
Blanes	Selva	39834
Boadella i les Escaules	Alt Empordà	253
Bolvir	Cerdanya	393
Bonastre	Baix Penedès	642
Es Bòrdes	Val d'Aran	242
Bordils	Gironès	1736
Les Borges Blanques	Garrigues	6034
Les Borges del Camp	Baix Camp	2146
Borrassà	Alt Empordà	709
Borredà	Berguedà	595
Bossòst	Val d'Aran	1168
Bot	Terra Alta	693
Botarell	Baix Camp	1109
Bovera	Garrigues	332
Bràfim	Alt Camp	670
Breda	Selva	3781
El Bruc	Anoia	1992
El Brull	Osona	249
Brunyola	Selva	388
Cabacés	Priorat	340
Cabanabona	Noguera	112
Cabanelles	Alt Empordà	247
Cabanes	Alt Empordà	912
Les Cabanyes	Alt Penedès	927
Cabó	Alt Urgell	94
Cabra del Camp	Alt Camp	1152
Cabrera d'Anoia	Anoia	1355
Cabrera de Mar	Maresme	4528
Cabrils	Maresme	7196
Cadaqués	Alt Empordà	2902
Calaf	Anoia	3522
Calafell	Baix Penedès	24984
Calders	Bages	955
Caldes de Malavella	Selva	6998
Caldes de Montbui	Vallès Oriental	17186
Caldes d'Estrac	Maresme	2776
Calella	Maresme	18694
Calldetenes	Osona	2426
Callús	Bages	1940
Calonge	Baix Empordà	10761
Calonge de Segarra	Anoia	198
Camarasa	Noguera	949
Camarles	Baix Ebre	3600
Cambrils	Baix Camp	33008
Camós	Pla de l'Estany	684
Campdevànol	Ripollès	3477
Campelles	Ripollès	136
Campins	Vallès Oriental	480
Campllong	Gironès	497
Camprodon	Ripollès	2450
Canejan	Val d'Aran	104
Canet d'Adri	Gironès	609
Canet de Mar	Maresme	14072
La Canonja	Tarragonès	5673
Canovelles	Vallès Oriental	15851
Cànoves i Samalús	Vallès Oriental	2818
Cantallops	Alt Empordà	326
Canyelles	Garraf	4282
Capafonts	Baix Camp	123
Capçanes	Priorat	420
Capellades	Anoia	5494
Capmany	Alt Empordà	623
Capolat	Berguedà	85
Cardedeu	Vallès Oriental	17241
Cardona	Bages	5116
Carme	Anoia	836
Caseres	Terra Alta	292
Cassà de la Selva	Gironès	9789
Casserres	Berguedà	1595
Castell de l'Areny	Berguedà	70
Castell de Mur	Pallars Jussà	186
Castellar de la Ribera	Solsonès	156
Castellar de n'Hug	Berguedà	169
Castellar del Riu	Berguedà	174
Castellar del Vallès	Vallès Occidental	23238
Castellbell i el Vilar	Bages	3711
Castellbisbal	Vallès Occidental	12267
Castellcir	Vallès Oriental	665
Castelldans	Garrigues	1006
Castelldefels	Baix Llobregat	63139
Castellet i la Gornal	Alt Penedès	2223
Castellfollit de la Roca	Garrotxa	1002
Castellfollit de Riubregós	Anoia	190
Castellfollit del Boix	Bages	409
Castellgalí	Bages	1966
Castellnou de Bages	Bages	1091
Castellnou de Seana	Pla d'Urgell	745
Castelló de Farfanya	Noguera	559
Castelló d'Empúries	Alt Empordà	11885
Castellolí	Anoia	550
Castell-Platja d'Aro	Baix Empordà	10420
Castellserà	Urgell	1116
Castellterçol	Vallès Oriental	2376
Castellvell del Camp	Baix Camp	2792
Castellví de la Marca	Alt Penedès	1649
Castellví de Rosanes	Baix Llobregat	1792
El Catllar	Tarragonès	4148
Cava	Alt Urgell	61
La Cellera de Ter	Selva	2105
Celrà	Gironès	4772
Centelles	Osona	7360
Cercs	Berguedà	1303
Cerdanyola del Vallès	Vallès Occidental	58247
Cervelló	Baix Llobregat	8651
Cervera	Segarra	9390
Cervià de les Garrigues	Garrigues	808
Cervià de Ter	Gironès	895
Cistella	Alt Empordà	272
Ciutadilla	Urgell	210
Clariana de Cardener	Solsonès	157
El Cogul	Garrigues	188
Colera	Alt Empordà	593
Coll de Nargó	Alt Urgell	607
Collbató	Baix Llobregat	4242
Colldejou	Baix Camp	181
Collsuspina	Osona	347
Colomers	Baix Empordà	196
La Coma i la Pedra	Solsonès	275
Conca de Dalt	Pallars Jussà	420
Conesa	Conca de Barberà	129
Constantí	Tarragonès	6592
Copons	Anoia	332
Corbera de Llobregat	Baix Llobregat	14064
Corbera d'Ebre	Terra Alta	1180
Corbins	Segrià	1377
Corçà	Baix Empordà	1317
Cornellà de Llobregat	Baix Llobregat	87243
Cornellà del Terri	Pla de l'Estany	2233
Cornudella de Montsant	Priorat	1026
Creixell	Tarragonès	3386
Crespià	Pla de l'Estany	260
Cruïlles, Monells i Sant Sadurní de l'Heura	Baix Empordà	1282
Cubelles	Garraf	14293
Cubells	Noguera	400
Cunit	Baix Penedès	12551
Darnius	Alt Empordà	528
Das	Cerdanya	219
Deltebre	Baix Ebre	12302
Dosrius	Maresme	5123
Duesaigües	Baix Camp	236
L'Escala	Alt Empordà	10554
Esparreguera	Baix Llobregat	21986
Espinelves	Osona	199
L'Espluga Calba	Garrigues	430
L'Espluga de Francolí	Conca de Barberà	3923
Esplugues de Llobregat	Baix Llobregat	46687
Espolla	Alt Empordà	417
Esponellà	Pla de l'Estany	451
Espot	Pallars Sobirà	350
L'Espunyola	Berguedà	268
Estamariu	Alt Urgell	123
L'Estany	Bages	393
Estaràs	Segarra	170
Esterri d'Àneu	Pallars Sobirà	924
Esterri de Cardós	Pallars Sobirà	77
Falset	Priorat	2952
El Far d'Empordà	Alt Empordà	555
Farrera	Pallars Sobirà	140
La Fatarella	Terra Alta	1111
La Febró	Baix Camp	51
Figaró-Montmany	Vallès Oriental	1112
Fígols	Berguedà	52
Fígols i Alinyà	Alt Urgell	282
La Figuera	Priorat	133
Figueres	Alt Empordà	44765
Figuerola del Camp	Alt Camp	349
Flaçà	Gironès	1059
Flix	Ribera d'Ebre	3969
La Floresta	Garrigues	168
Fogars de la Selva	Selva	1498
Fogars de Montclús	Vallès Oriental	453
Foixà	Baix Empordà	318
Folgueroles	Osona	2229
Fondarella	Pla d'Urgell	834
Fonollosa	Bages	1417
Fontanals de Cerdanya	Cerdanya	465
Fontanilles	Baix Empordà	167
Fontcoberta	Pla de l'Estany	1349
Font-rubí	Alt Penedès	1466
Foradada	Noguera	183
Forallac	Baix Empordà	1785
Forès	Conca de Barberà	59
Fornells de la Selva	Gironès	2380
Fortià	Alt Empordà	658
Les Franqueses del Vallès	Vallès Oriental	18693
Freginals	Montsià	464
La Fuliola	Urgell	1286
Fulleda	Garrigues	105
Gaià	Bages	172
La Galera	Montsià	846
Gallifa	Vallès Occidental	204
Gandesa	Terra Alta	3219
Garcia	Ribera d'Ebre	580
Els Garidells	Alt Camp	191
La Garriga	Vallès Oriental	15236
Garrigàs	Alt Empordà	386
Garrigoles	Baix Empordà	164
Garriguella	Alt Empordà	863
Gavà	Baix Llobregat	46250
Gavet de la Conca	Pallars Jussà	302
Gelida	Alt Penedès	7085
Ger	Cerdanya	467
Gimenells i el Pla de la Font	Segrià	1179
Ginestar	Ribera d'Ebre	986
Girona	Gironès	96722
Gironella	Berguedà	5083
Gisclareny	Berguedà	31
Godall	Montsià	822
Golmés	Pla d'Urgell	1691
Gombrèn	Ripollès	209
Gósol	Berguedà	230
La Granada	Alt Penedès	1995
La Granadella	Garrigues	759
Granera	Vallès Oriental	80
La Granja d'Escarp	Segrià	968
Granollers	Vallès Oriental	60000
Granyanella	Segarra	149
Granyena de les Garrigues	Garrigues	172
Granyena de Segarra	Segarra	137
Gratallops	Priorat	264
Gualba	Vallès Oriental	1312
Gualta	Baix Empordà	358
Guardiola de Berguedà	Berguedà	1027
Els Guiamets	Priorat	322
Guils de Cerdanya	Cerdanya	565
Guimerà	Urgell	320
La Guingueta d'Àneu	Pallars Sobirà	347
Guissona	Segarra	6552
Guixers	Solsonès	134
Gurb	Osona	2538
Horta de Sant Joan	Terra Alta	1295
L'Hospitalet de Llobregat	Barcelonès	256065
Els Hostalets de Pierola	Anoia	2827
Hostalric	Selva	4030
Igualada	Anoia	39191
Isona i Conca Dellà	Pallars Jussà	1100
Isòvol	Cerdanya	322
Ivars de Noguera	Noguera	357
Ivars d'Urgell	Pla d'Urgell	1702
Ivorra	Segarra	120
Jafre	Baix Empordà	413
La Jonquera	Alt Empordà	3094
Jorba	Anoia	820
Josa i Tuixén	Alt Urgell	136
Juià	Gironès	338
Juncosa	Garrigues	470
Juneda	Garrigues	3482
Les	Val d'Aran	1005
Linyola	Pla d'Urgell	2712
La Llacuna	Anoia	935
Lladó	Alt Empordà	713
Lladorre	Pallars Sobirà	244
Lladurs	Solsonès	197
La Llagosta	Vallès Oriental	13721
Llagostera	Gironès	8105
Llambilles	Gironès	717
Llanars	Ripollès	561
Llançà	Alt Empordà	5140
Llardecans	Segrià	515
Llavorsí	Pallars Sobirà	373
Lleida	Segrià	138416
Llers	Alt Empordà	1193
Lles de Cerdanya	Cerdanya	268
Lliçà d'Amunt	Vallès Oriental	14456
Lliçà de Vall	Vallès Oriental	6404
Llimiana	Pallars Jussà	183
Llinars del Vallès	Vallès Oriental	9293
Llívia	Cerdanya	1665
El Lloar	Priorat	119
Llobera	Solsonès	210
Llorac	Conca de Barberà	112
Llorenç del Penedès	Baix Penedès	2245
Lloret de Mar	Selva	40282
Les Llosses	Ripollès	221
Lluçà	Osona	254
Maçanet de Cabrenys	Alt Empordà	735
Maçanet de la Selva	Selva	7099
Madremanya	Gironès	260
Maià de Montcal	Garrotxa	432
Maials	Segrià	969
Maldà	Urgell	250
Malgrat de Mar	Maresme	18444
Malla	Osona	259
Manlleu	Osona	20445
Manresa	Bages	76589
Marçà	Priorat	638
Margalef	Priorat	115
Marganell	Bages	311
Martorell	Baix Llobregat	27457
Martorelles	Vallès Oriental	4903
Mas de Barberans	Montsià	635
Masarac	Alt Empordà	296
Masdenverge	Montsià	1131
Les Masies de Roda	Osona	763
Les Masies de Voltregà	Osona	3174
Masllorenç	Baix Penedès	538
El Masnou	Maresme	22523
La Masó	Alt Camp	293
Maspujols	Baix Camp	730
Masquefa	Anoia	8310
El Masroig	Priorat	562
Massalcoreig	Segrià	581
Massanes	Selva	700
Massoteres	Segarra	205
Matadepera	Vallès Occidental	8584
Mataró	Maresme	123868
Mediona	Alt Penedès	2347
Menàrguens	Noguera	903
Meranges	Cerdanya	96
Mieres	Garrotxa	335
El Milà	Alt Camp	183
Miralcamp	Pla d'Urgell	1429
Miravet	Ribera d'Ebre	770
Moià	Bages	5730
El Molar	Priorat	305
Molins de Rei	Baix Llobregat	24572
Mollerussa	Pla d'Urgell	14705
Mollet de Peralada	Alt Empordà	178
Mollet del Vallès	Vallès Oriental	52409
Molló	Ripollès	358
La Molsosa	Solsonès	116
Monistrol de Calders	Bages	689
Monistrol de Montserrat	Bages	3009
Montagut i Oix	Garrotxa	983
Montblanc	Conca de Barberà	7354
Montbrió del Camp	Baix Camp	2461
Montcada i Reixac	Vallès Occidental	34232
Montclar	Berguedà	112
Montellà i Martinet	Cerdanya	683
Montesquiu	Osona	901
Montferrer i Castellbò	Alt Urgell	1083
Montferri	Alt Camp	405
Montgai	Noguera	720
Montgat	Maresme	10739
Montmajor	Berguedà	475
Montmaneu	Anoia	196
El Montmell	Baix Penedès	1509
Montmeló	Vallès Oriental	8913
Montoliu de Lleida	Segrià	505
Montoliu de Segarra	Segarra	196
Montornès de Segarra	Segarra	98
Montornès del Vallès	Vallès Oriental	16042
Mont-ral	Alt Camp	175
Mont-ras	Baix Empordà	1833
Mont-roig del Camp	Baix Camp	12476
Montseny	Vallès Oriental	314
Móra d'Ebre	Ribera d'Ebre	5699
Móra la Nova	Ribera d'Ebre	3289
El Morell	Tarragonès	3445
La Morera de Montsant	Priorat	164
Muntanyola	Osona	568
Mura	Bages	230
Nalec	Urgell	99
Naut Aran	Val d'Aran	1760
Navarcles	Bages	5965
Navàs	Bages	6171
Navata	Alt Empordà	1227
Navès	Solsonès	277
La Nou de Berguedà	Berguedà	147
La Nou de Gaià	Tarragonès	535
Nulles	Alt Camp	461
Odèn	Solsonès	273
Òdena	Anoia	3469
Ogassa	Ripollès	251
Olèrdola	Alt Penedès	3584
Olesa de Bonesvalls	Alt Penedès	1762
Olesa de Montserrat	Baix Llobregat	23924
Oliana	Alt Urgell	1942
Oliola	Noguera	230
Olius	Solsonès	870
Olivella	Garraf	3589
Olost	Osona	1191
Olot	Garrotxa	33725
Les Oluges	Segarra	174
Olvan	Berguedà	908
Els Omellons	Garrigues	241
Els Omells de na Gaia	Urgell	146
Ordis	Alt Empordà	379
Organyà	Alt Urgell	929
Orís	Osona	291
Oristà	Osona	569
Orpí	Anoia	172
Òrrius	Maresme	644
Os de Balaguer	Noguera	987
Osor	Selva	456
Ossó de Sió	Urgell	218
Pacs del Penedès	Alt Penedès	872
Palafolls	Maresme	8966
Palafrugell	Baix Empordà	22816
Palamós	Baix Empordà	17918
El Palau d'Anglesola	Pla d'Urgell	2172
Palau de Santa Eulàlia	Alt Empordà	104
Palau-sator	Baix Empordà	294
Palau-saverdera	Alt Empordà	1488
Palau-solità i Plegamans	Vallès Occidental	14352
Els Pallaresos	Tarragonès	4265
Pallejà	Baix Llobregat	11272
La Palma de Cervelló	Baix Llobregat	3019
La Palma d'Ebre	Ribera d'Ebre	417
Palol de Revardit	Pla de l'Estany	471
Pals	Baix Empordà	2725
El Papiol	Baix Llobregat	3941
Pardines	Ripollès	159
Parets del Vallès	Vallès Oriental	18113
Parlavà	Baix Empordà	383
Passanant i Belltall	Conca de Barberà	168
Pau	Alt Empordà	589
Paüls	Baix Ebre	605
Pedret i Marzà	Alt Empordà	175
Penelles	Noguera	505
La Pera	Baix Empordà	435
Perafita	Osona	400
Perafort	Tarragonès	1230
Peralada	Alt Empordà	1846
Peramola	Alt Urgell	384
El Perelló	Baix Ebre	3336
Piera	Anoia	14867
Les Piles	Conca de Barberà	219
Pineda de Mar	Maresme	26040
El Pinell de Brai	Terra Alta	1133
Pinell de Solsonès	Solsonès	217
Pinós	Solsonès	307
Pira	Conca de Barberà	500
El Pla de Santa Maria	Alt Camp	2385
El Pla del Penedès	Alt Penedès	1145
Les Planes d'Hostoles	Garrotxa	1708
Planoles	Ripollès	309
Els Plans de Sió	Segarra	559
El Poal	Pla d'Urgell	645
La Pobla de Cérvoles	Garrigues	245
La Pobla de Claramunt	Anoia	2269
La Pobla de Lillet	Berguedà	1295
La Pobla de Mafumet	Tarragonès	2810
La Pobla de Massaluca	Terra Alta	377
La Pobla de Montornès	Tarragonès	2902
La Pobla de Segur	Pallars Jussà	3246
Poboleda	Priorat	383
Polinyà	Vallès Occidental	7984
El Pont d'Armentera	Alt Camp	583
El Pont de Bar	Alt Urgell	190
Pont de Molins	Alt Empordà	509
El Pont de Suert	Alta Ribagorça	2517
El Pont de Vilomara i Rocafort	Bages	3741
Pontils	Conca de Barberà	134
Pontons	Alt Penedès	572
Pontós	Alt Empordà	233
Ponts	Noguera	2714
Porqueres	Pla de l'Estany	4431
Porrera	Priorat	468
El Port de la Selva	Alt Empordà	1009
Portbou	Alt Empordà	1290
La Portella	Segrià	754
Pradell de la Teixeta	Priorat	204
Prades	Baix Camp	662
Prat de Comte	Terra Alta	190
El Prat de Llobregat	Baix Llobregat	63499
Pratdip	Baix Camp	848
Prats de Lluçanès	Osona	2676
Els Prats de Rei	Anoia	532
Prats i Sansor	Cerdanya	284
Preixana	Urgell	426
Preixens	Noguera	477
Premià de Dalt	Maresme	10168
Premià de Mar	Maresme	28310
Les Preses	Garrotxa	1745
Prullans	Cerdanya	234
Puigcerdà	Cerdanya	8802
Puigdàlber	Alt Penedès	525
Puiggròs	Garrigues	314
Puigpelat	Alt Camp	1022
Puig-reig	Berguedà	4347
Puigverd d'Agramunt	Urgell	281
Puigverd de Lleida	Segrià	1422
Pujalt	Anoia	208
La Quar	Berguedà	66
Quart	Gironès	3150
Queralbs	Ripollès	186
Querol	Alt Camp	544
Rabós	Alt Empordà	196
Rajadell	Bages	524
Rasquera	Ribera d'Ebre	962
Regencós	Baix Empordà	301
Rellinars	Vallès Occidental	738
Renau	Tarragonès	138
Reus	Baix Camp	106709
Rialp	Pallars Sobirà	664
La Riba	Alt Camp	681
Riba-roja d'Ebre	Ribera d'Ebre	1321
Ribera d'Ondara	Segarra	459
Ribera d'Urgellet	Alt Urgell	975
Ribes de Freser	Ripollès	1941
Riells i Viabrea	Selva	3993
La Riera de Gaià	Tarragonès	1677
Riner	Solsonès	283
Ripoll	Ripollès	10913
Ripollet	Vallès Occidental	37348
Riu de Cerdanya	Cerdanya	113
Riudarenes	Selva	2183
Riudaura	Garrotxa	439
Riudecanyes	Baix Camp	1154
Riudecols	Baix Camp	1294
Riudellots de la Selva	Selva	2022
Riudoms	Baix Camp	6466
Riumors	Alt Empordà	247
La Roca del Vallès	Vallès Oriental	10303
Rocafort de Queralt	Conca de Barberà	244
Roda de Barà	Tarragonès	6284
Roda de Ter	Osona	6151
Rodonyà	Alt Camp	500
Roquetes	Baix Ebre	8280
Roses	Alt Empordà	19731
Rosselló	Segrià	3030
El Rourell	Alt Camp	386
Rubí	Vallès Occidental	73979
Rubió	Anoia	222
Rupià	Baix Empordà	241
Rupit i Pruit	Osona	309
Sabadell	Vallès Occidental	207721
Sagàs	Berguedà	140
Salàs de Pallars	Pallars Jussà	353
Saldes	Berguedà	324
Sales de Llierca	Garrotxa	144
Sallent	Bages	6892
Salomó	Tarragonès	525
Salou	Tarragonès	26193
Salt	Gironès	30389
Sanaüja	Segarra	460
Sant Adrià de Besòs	Barcelonès	34157
Sant Agustí de Lluçanès	Osona	96
Sant Andreu de la Barca	Baix Llobregat	27094
Sant Andreu de Llavaneres	Maresme	10406
Sant Andreu Salou	Gironès	152
Sant Aniol de Finestres	Garrotxa	345
Sant Antoni de Vilamajor	Vallès Oriental	5555
Sant Bartomeu del Grau	Osona	963
Sant Boi de Llobregat	Baix Llobregat	82860
Sant Boi de Lluçanès	Osona	523
Sant Carles de la Ràpita	Montsià	15338
Sant Cebrià de Vallalta	Maresme	3426
Sant Celoni	Vallès Oriental	16949
Sant Climent de Llobregat	Baix Llobregat	3907
Sant Climent Sescebes	Alt Empordà	545
Sant Cugat del Vallès	Vallès Occidental	83337
Sant Cugat Sesgarrigues	Alt Penedès	992
Sant Esteve de la Sarga	Pallars Jussà	138
Sant Esteve de Palautordera	Vallès Oriental	2516
Sant Esteve Sesrovires	Baix Llobregat	7439
Sant Feliu de Buixalleu	Selva	768
Sant Feliu de Codines	Vallès Oriental	5990
Sant Feliu de Guíxols	Baix Empordà	21814
Sant Feliu de Llobregat	Baix Llobregat	43096
Sant Feliu de Pallerols	Garrotxa	1330
Sant Feliu Sasserra	Bages	669
Sant Ferriol	Garrotxa	228
Sant Fost de Campsentelles	Vallès Oriental	8421
Sant Fruitós de Bages	Bages	8198
Sant Gregori	Gironès	3280
Sant Guim de Freixenet	Segarra	1111
Sant Guim de la Plana	Segarra	195
Sant Hilari Sacalm	Selva	5724
Sant Hipòlit de Voltregà	Osona	3547
Sant Iscle de Vallalta	Maresme	1281
Sant Jaume de Frontanyà	Berguedà	19
Sant Jaume de Llierca	Garrotxa	774
Sant Jaume dels Domenys	Baix Penedès	2505
Sant Jaume d'Enveja	Montsià	3541
Sant Joan de les Abadesses	Ripollès	3492
Sant Joan de Mollet	Gironès	522
Sant Joan de Vilatorrada	Bages	10767
Sant Joan Despí	Baix Llobregat	32406
Sant Joan les Fonts	Garrotxa	2877
Sant Jordi Desvalls	Gironès	667
Sant Julià de Cerdanyola	Berguedà	263
Sant Julià de Ramis	Gironès	3348
Sant Julià de Vilatorta	Osona	2984
Sant Julià del Llor i Bonmatí	Selva	1271
Sant Just Desvern	Baix Llobregat	16253
Sant Llorenç de la Muga	Alt Empordà	227
Sant Llorenç de Morunys	Solsonès	1032
Sant Llorenç d'Hortons	Alt Penedès	2492
Sant Llorenç Savall	Vallès Occidental	2412
Sant Martí d'Albars	Osona	109
Sant Martí de Centelles	Osona	1080
Sant Martí de Llémena	Gironès	591
Sant Martí de Riucorb	Urgell	683
Sant Martí de Tous	Anoia	1167
Sant Martí Sarroca	Alt Penedès	3197
Sant Martí Sesgueioles	Anoia	376
Sant Martí Vell	Gironès	258
Sant Mateu de Bages	Bages	642
Sant Miquel de Campmajor	Pla de l'Estany	234
Sant Miquel de Fluvià	Alt Empordà	764
Sant Mori	Alt Empordà	193
Sant Pau de Segúries	Ripollès	694
Sant Pere de Ribes	Garraf	28783
Sant Pere de Riudebitlles	Alt Penedès	2382
Sant Pere de Torelló	Osona	2423
Sant Pere de Vilamajor	Vallès Oriental	4256
Sant Pere Pescador	Alt Empordà	2108
Sant Pere Sallavinera	Anoia	164
Sant Pol de Mar	Maresme	5070
Sant Quintí de Mediona	Alt Penedès	2147
Sant Quirze de Besora	Osona	2201
Sant Quirze del Vallès	Vallès Occidental	19051
Sant Quirze Safaja	Vallès Oriental	661
Sant Ramon	Segarra	552
Sant Sadurní d'Anoia	Alt Penedès	12345
Sant Sadurní d'Osormort	Osona	95
Sant Salvador de Guardiola	Bages	3146
Sant Vicenç de Castellet	Bages	9126
Sant Vicenç de Montalt	Maresme	5854
Sant Vicenç de Torelló	Osona	2049
Sant Vicenç dels Horts	Baix Llobregat	28137
Santa Bàrbara	Montsià	3989
Santa Cecília de Voltregà	Osona	182
Santa Coloma de Cervelló	Baix Llobregat	7931
Santa Coloma de Farners	Selva	12305
Santa Coloma de Gramenet	Barcelonès	120824
Santa Coloma de Queralt	Conca de Barberà	3092
Santa Cristina d'Aro	Baix Empordà	5066
Santa Eugènia de Berga	Osona	2294
Santa Eulàlia de Riuprimer	Osona	1123
Santa Eulàlia de Ronçana	Vallès Oriental	6921
Santa Fe del Penedès	Alt Penedès	408
Santa Llogaia d'Àlguema	Alt Empordà	342
Santa Margarida de Montbui	Anoia	9812
Santa Margarida i els Monjos	Alt Penedès	7030
Santa Maria de Besora	Osona	160
Santa Maria de Corcó	Osona	2216
Santa Maria de Martorelles	Vallès Oriental	841
Santa Maria de Merlès	Berguedà	171
Santa Maria de Miralles	Anoia	140
Santa Maria de Palautordera	Vallès Oriental	9097
Santa Maria d'Oló	Bages	1066
Santa Oliva	Baix Penedès	3343
Santa Pau	Garrotxa	1601
Santa Perpètua de Mogoda	Vallès Occidental	25331
Santa Susanna	Maresme	3317
Santpedor	Bages	7185
Sarral	Conca de Barberà	1703
Sarrià de Ter	Gironès	4714
Sarroca de Bellera	Pallars Jussà	127
Sarroca de Lleida	Segrià	433
Saus, Camallera i Llampaies	Alt Empordà	780
Savallà del Comtat	Conca de Barberà	69
La Secuita	Tarragonès	1582
La Selva de Mar	Alt Empordà	209
La Selva del Camp	Baix Camp	5576
Senan	Conca de Barberà	55
La Sénia	Montsià	6045
Senterada	Pallars Jussà	135
La Sentiu de Sió	Noguera	488
Sentmenat	Vallès Occidental	8407
Serinyà	Pla de l'Estany	1117
Seròs	Segrià	1910
Serra de Daró	Baix Empordà	209
Setcases	Ripollès	176
La Seu d'Urgell	Alt Urgell	13009
Seva	Osona	3412
Sidamon	Pla d'Urgell	739
Sils	Selva	5492
Sitges	Garraf	28617
Siurana	Alt Empordà	181
Sobremunt	Osona	88
El Soleràs	Garrigues	369
Solivella	Conca de Barberà	687
Solsona	Solsonès	9304
Sora	Osona	179
Soriguera	Pallars Sobirà	368
Sort	Pallars Sobirà	2360
Soses	Segrià	1764
Subirats	Alt Penedès	3075
Sudanell	Segrià	885
Sunyer	Segrià	305
Súria	Bages	6255
Susqueda	Selva	115
Tagamanent	Vallès Oriental	314
Talamanca	Bages	155
Talarn	Pallars Jussà	523
Talavera	Segarra	290
La Tallada d'Empordà	Baix Empordà	449
Taradell	Osona	6181
Tarragona	Tarragonès	134085
Tàrrega	Urgell	17129
Tarrés	Garrigues	108
Tarroja de Segarra	Segarra	175
Tavèrnoles	Osona	307
Tavertet	Osona	142
Teià	Maresme	6162
Térmens	Noguera	1521
Terrades	Alt Empordà	311
Terrassa	Vallès Occidental	213697
Tiana	Maresme	7973
Tírvia	Pallars Sobirà	160
Tiurana	Noguera	83
Tivenys	Baix Ebre	910
Tivissa	Ribera d'Ebre	1824
Tona	Osona	8119
Torà	Segarra	1343
Tordera	Maresme	15974
Torelló	Osona	13931
Els Torms	Garrigues	171
Tornabous	Urgell	871
La Torre de Cabdella	Pallars Jussà	769
La Torre de Claramunt	Anoia	3796
La Torre de Fontaubella	Priorat	140
La Torre de l'Espanyol	Ribera d'Ebre	698
Torrebesses	Segrià	300
Torredembarra	Tarragonès	15461
Torrefarrera	Segrià	4309
Torrefeta i Florejacs	Segarra	634
Torregrossa	Pla d'Urgell	2241
Torrelameu	Noguera	714
Torrelavit	Alt Penedès	1398
Torrelles de Foix	Alt Penedès	2454
Torrelles de Llobregat	Baix Llobregat	5661
Torrent	Baix Empordà	189
Torres de Segre	Segrià	2146
Torre-serona	Segrià	348
Torroella de Fluvià	Alt Empordà	699
Torroella de Montgrí	Baix Empordà	11385
Torroja del Priorat	Priorat	171
Tortellà	Garrotxa	760
Tortosa	Baix Ebre	34432
Toses	Ripollès	161
Tossa de Mar	Selva	5917
Tremp	Pallars Jussà	6711
Ullà	Baix Empordà	1075
Ullastrell	Vallès Occidental	1904
Ullastret	Baix Empordà	268
Ulldecona	Montsià	7404
Ulldemolins	Priorat	449
Ultramort	Baix Empordà	211
Urús	Cerdanya	204
Vacarisses	Vallès Occidental	6175
La Vajol	Alt Empordà	101
La Vall de Bianya	Garrotxa	1315
La Vall de Boí	Alta Ribagorça	1076
Vall de Cardós	Pallars Sobirà	404
La Vall d'en Bas	Garrotxa	2888
Vallbona d'Anoia	Anoia	1433
Vallbona de les Monges	Urgell	264
Vallcebre	Berguedà	269
Vallclara	Conca de Barberà	125
Vallfogona de Balaguer	Noguera	1847
Vallfogona de Ripollès	Ripollès	223
Vallfogona de Riucorb	Conca de Barberà	115
Vallgorguina	Vallès Oriental	2617
Vallirana	Baix Llobregat	14409
Vall-llobrega	Baix Empordà	877
Vallmoll	Alt Camp	1651
Vallromanes	Vallès Oriental	2396
Valls	Alt Camp	25016
Les Valls d'Aguilar	Alt Urgell	305
Les Valls de Valira	Alt Urgell	953
Vandellòs i l'Hospitalet de l'Infant	Baix Camp	5941
La Vansa i Fórnols	Alt Urgell	214
Veciana	Anoia	173
El Vendrell	Baix Penedès	36453
Ventalló	Alt Empordà	800
Verdú	Urgell	1006
Verges	Baix Empordà	1207
Vespella de Gaià	Tarragonès	415
Vic	Osona	40900
Vidrà	Osona	167
Vidreres	Selva	7661
Vielha e Mijaran	Val d'Aran	5601
Vilabella	Alt Camp	826
Vilabertran	Alt Empordà	902
Vilablareix	Gironès	2401
Vilada	Berguedà	509
Viladamat	Alt Empordà	458
Viladasens	Gironès	210
Viladecans	Baix Llobregat	64737
Viladecavalls	Vallès Occidental	7376
Vilademuls	Pla de l'Estany	780
Viladrau	Osona	1102
Vilafant	Alt Empordà	5465
Vilafranca del Penedès	Alt Penedès	38785
Vilagrassa	Urgell	471
Vilajuïga	Alt Empordà	1166
Vilalba dels Arcs	Terra Alta	711
Vilalba Sasserra	Vallès Oriental	670
Vilaller	Alta Ribagorça	691
Vilallonga de Ter	Ripollès	476
Vilallonga del Camp	Tarragonès	2181
Vilamacolum	Alt Empordà	299
Vilamalla	Alt Empordà	1115
Vilamaniscle	Alt Empordà	171
Vilamòs	Val d'Aran	189
Vilanant	Alt Empordà	373
Vilanova de Bellpuig	Pla d'Urgell	1206
Vilanova de la Barca	Segrià	1185
Vilanova de l'Aguda	Noguera	236
Vilanova de Meià	Noguera	422
Vilanova de Prades	Conca de Barberà	133
Vilanova de Sau	Osona	335
Vilanova de Segrià	Segrià	870
Vilanova del Camí	Anoia	12632
Vilanova del Vallès	Vallès Oriental	4975
Vilanova d'Escornalbou	Baix Camp	568
Vilanova i la Geltrú	Garraf	66905
Vilaplana	Baix Camp	639
Vila-rodona	Alt Camp	1279
Vila-sacra	Alt Empordà	656
Vila-sana	Pla d'Urgell	698
Vila-seca	Tarragonès	21839
Vilassar de Dalt	Maresme	8794
Vilassar de Mar	Maresme	19840
Vilaür	Alt Empordà	149
Vilaverd	Conca de Barberà	504
La Vilella Alta	Priorat	140
La Vilella Baixa	Priorat	210
Vilobí del Penedès	Alt Penedès	1103
Vilobí d'Onyar	Selva	3031
Vilopriu	Baix Empordà	212
Vimbodí i Poblet	Conca de Barberà	1010
Vinaixa	Garrigues	574
Vinebre	Ribera d'Ebre	460
Vinyols i els Arcs	Baix Camp	1911
Viver i Serrateix	Berguedà	178
Xerta	Baix Ebre
 **/
