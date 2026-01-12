# BMO
## Descrierea realizarii:
> [!NOTE]
> Asta e tot ce depinde de descriere:

Sistemul functioneaza prin sincronizarea orei setate pe PC cu ora sistemului. La momentul potrivit, se declanseaza un semnal sonor si vizual, iar motoarele integrate in sistem efectueaza o miscare de rotatie pentru a indica administrarea medicamentelor.  
Programul in python afiseaza timpii pt debugging.

## Schema electrica include:

-Microcontrolerul (Arduino) pentru gestionarea functiilor de baza;  
-Afisaj LCD pentru afisarea orei curente;  
-Buzzer pentru emiterea semnalului sonor;  
-Led verde pentru semnalul vizual;  
-Motoare pentru rotatie;  
-Conexiune cu PC-ul pentru setarea initiala a orei. Fiecare componenta este configurata pentru a permite coordonarea precisa a actiunilor.  

### Se prezinta si problemele nerezolvate cu motivarea lor:

- [ ]Extinderea alertelor audio personalizabile.  
- [ ]Adaugarea unei baterii (nu am gasit un cablu conector in casa);  
- [ ]Timpul eliberarii pastilelor poate fi schimbat doar din cod.  
- [ ]Un modul RTC (ceas) sau ceas care se poate seta din butoane (scump, asa ca am facut un program in Python care transmite direct ora laptopului).
    
Link-uri: [Sonerie](https://projecthub.arduino.cc/tmekinyan/playing-popular-songs-with-arduino-and-a-buzzer-546f4a).
