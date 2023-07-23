#include <SoftwareSerial.h>
#include <ArduinoJson.h>  // Converter em Json

SoftwareSerial HC12(D3, D4);  // Esp8266
// Rx pino D1 (Ligar no Tx do outro)
// Tx pino D2 (Ligar no Rx do outro)
int corte = 200;

String txt = "LoremipsumdolorsitametconsecteturadipiscingelitseddoeiusmodtemporincididuntutlaboreetdoloremagnaaliquaSitametcommodonullafacilisinullamvehiculaipsumSemettortorconsequatidUltricessagittisorciascelerisquepurussemperegetduisActortorvitaepurusfaucibusHabitasseplateadictumstquisquesagittispurussitAtlectusurnaduisconvallisconvallistellusidinterdumEnimtortoratauctorurnaUteusemintegervitaejustoegetTristiquesollicitudinnibhsitametcommodonullafacilisinullamvehiculaNecullamcorpersitametrisusnullamVelpharetravelturpisnuncegetQuisblanditturpiscursusinVenenatiscrassedfelisegetvelitaliquetsagittiNibhsedpulvinarproingravidahendreritScelerisquefelisimperdietproinfermentumleovelNullamegetfelisegetnunclobortismattisUtvenenatistellusinmetusvulputateeuSapienfaucibusetmolestieacQuisenimlobortisscelerisquefermentumduifaucibusinGravidanequeconvallisacrasSedliberoenimsedfaucibusturpisineuAeratnamatlectusurnaduisTempusegestassedsedrisuspretiumquamEgetmaurispharetraetultricesnequeornareaeneaneuismodelementumSitametaliquamiddiamPellentesquedignissimenimsitametvenenatisurnacursusegetnuncAdipiscingatintellusintegerfeugiatscelerisqueOdiotempororcidapibusultricesiniaculisnuncsedaugueRhoncusaeneanvelelitscelerisquemaurispellentesquepulvinarGravidacumsociisnatoquepenatibusetmagnisQuisvariusquamquisqueiddiamEusemintegervitaejustoegetmagnafermentumiaculisConsecteturaeratnamatlectusurnaSedpulvinarproingravidahendreritlectusaMagnaetiamtempororcieulobortisSedarcunonodioeuismodlaciniaAliquamvestibulummorbiblanditcursusrisusNamliberojustolaoreetsitQuisviverranibhcraspulvinarDignissimcrastinciduntlobortisfeugiatvivamusataugueegetCursusrisusatultricesmiEgetmiproinsedliberoenimsedfaucibusturpisinAcutconsequatsemperviverraAmetcommodonullafacilisinullamvehiculaipsumSitamettelluscrasadipiscingOdioutsemnullapharetradiamsitametPraesentelementumfacilisisleovelfringillaestullamcorperegetCommodonullafacilisinullamvehiculaipsumaarcucursusTinciduntnuncpulvinarsapienetligulaullamcorperAugueinterdumveliteuismodinCrassemperauctornequevitaetempusquampellentesquenecAliquamultricessagittisorciascelerisqueAeneanpharetramagnaacplaceratArcuactortordignissimconvallisGravidarutrumquisquenontellusorciacNibhsedpulvinarproingravidahendreritlectusUtdiamquamnullaporttitormassaidnequeConvallisacrassemperauctorViverratellusinhachabitasseAdipiscingenimeuturpisegestaspretiumaeneanpharetramagnaSedvulputateodioutenimblanditvolutpatmaecenasvolutpatblanditAmetmauriscommodoquisimperdietmassatinciduntNibhmauriscursusmattismolestieaiaculisateratpellentesqueSitametvenenatisurnacursusAcodiotempororcidapibusultricesiniaculisQuisqueegestasdiaminarcucursuseuismodquisviverranibhFelisegetnunclobortismattisaliquamfaucibuspurusinmassaQuislectusnullaatvolutpatdiamutBibendumestultriciesintegerquisauctorelitOrnareaeneaneuismodelementumnisiquiseleifendquamEratimperdietsedeuismodnisiportaloremmollisAdipiscingelitpellentesquehabitantmorbitristiquesenectusetnetusetCongueeuconsequatacfelisdonecetTemporideunislnuncmiipsumfaucibusvitaealiquetInachoquedacerto";

// void protocolo() {
//   int tam = txt.length(), i;
//   String numeroHex;
//   StaticJsonDocument<20> tamanho;

//   tamanho["000"] = tam;

//   serializeJson(tamanho, HC12);

//   delay(2000);

//   for (i = 0; i < (tam / corte); i++) {
//     StaticJsonDocument<300> data;

//     numeroHex = i + 1;

//     if (i + 1 == (tam / corte) && (tam % corte) == 0) {
//       numeroHex = "###";
//     } else if (numeroHex.length() % 3 != 0) {
//       while (numeroHex.length() % 3 != 0) {
//         numeroHex = "0" + numeroHex;
//       }
//     }

//     data[numeroHex] = txt.substring(i * corte, (i + 1) * corte);

//     serializeJson(data, HC12);  // Escreve os dados no HC12

//     while (HC12.available()) {
//       i = HC12.read();
//       Serial.println(i);
//     }

//     delay(2000);
//   }

//   if ((tam % corte) != 0) {
//     StaticJsonDocument<300> data;

//     data["###"] = txt.substring(i * corte, (i + 1) * corte);

//     serializeJson(data, HC12);  // Escreve os dados no HC12

//     delay(1000);

//     while (HC12.available()) {
//       Serial.println(HC12.read());
//       i = HC12.read();
//     }

//     delay(1000);
//   }
// }

void protocolo(int i) {
  int tam = txt.length(), k, j;
  String numeroHex;
  StaticJsonDocument<20> tamanho;

  if (i == 0) {
    tamanho["000"] = tam;

    serializeJson(tamanho, HC12);

    delay(2000);
  }


  for (k = i; i < (tam / corte); i++) {
    StaticJsonDocument<300> data;
    numeroHex = i + 1;

    if (i + 1 == (tam / corte) && (tam % corte) == 0) {
      numeroHex = "###";
    } else if (numeroHex.length() % 3 != 0) {
      while (numeroHex.length() % 3 != 0) {
        numeroHex = "0" + numeroHex;
      }
    }

    data[numeroHex] = txt.substring(i * corte, (i + 1) * corte);

    serializeJson(data, HC12);  // Escreve os dados no HC12

    while (HC12.available()) {
      j = HC12.read();
      Serial.println(j);
      protocolo(j - 1);
    }

    delay(2000);
  }

  if ((tam % corte) != 0) {
    StaticJsonDocument<300> data;

    data["###"] = txt.substring(i * corte, (i + 1) * corte);

    serializeJson(data, HC12);  // Escreve os dados no HC12

    while (HC12.available()) {
      j = HC12.read();
      protocolo(j);
    }

    delay(2000);
  }

  while (HC12.available()) {
    j = HC12.read();
    protocolo(j);
  }

  delay(2000);
}


void setup() {
  Serial.begin(2400);  // Porta Serial do computador
  HC12.begin(2400);    // Porta Serial do HC12
}
void loop() {
  delay(3000);


  protocolo(0);
  // HC12.write("TESTANDO"); // Escreve os dados no HC12
  // HC12.flush();              // Aguarda os dados, depois limpa a memória
  delay(8000);
}