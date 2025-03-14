//QUIZZ MOSASAURE "VITESSE PLONGEE"

const int ledVerte = 11; //Led Verte
const int ledRouge = 12; //Led Rouge

const int questions[] = {2, 3}; // Boutons de gauche
const int reponses[] = {4, 5, 6, 7, 8, 9, 10}; // Boutons de droite

const int correspondances[][7] = {
    {4, -1, -1, -1, -1, -1, 10}, // Solutions question 1 
    {-1, -1, -6, 7, -1, -1, -1}, // Solutions question 2 
 };

const int nbQuestions = sizeof(questions) / sizeof(questions[0]);
const int nbReponses = sizeof(reponses) / sizeof(reponses[0]);
const int maxReponses = sizeof(correspondances[0]) / sizeof(correspondances[0][0]);

void setup() {
    Serial.begin(9600);
    pinMode(ledVerte, OUTPUT);
    pinMode(ledRouge, OUTPUT);
    
    for (int i = 0; i < nbQuestions; i++) {
        pinMode(questions[i], INPUT_PULLUP);
    }
    for (int i = 0; i < nbReponses; i++) {
        pinMode(reponses[i], INPUT_PULLUP);
    }
}

void loop() {
    int questionAppuyee = -1;
    int reponseAppuyee = -1;
    int nbBoutonsAppuyes = 0;

    for (int i = 0; i < nbQuestions; i++) {
        if (digitalRead(questions[i]) == LOW) {
            questionAppuyee = i;
            nbBoutonsAppuyes++;
        }
    }
    
    for (int j = 0; j < nbReponses; j++) {
        if (digitalRead(reponses[j]) == LOW) {
            reponseAppuyee = reponses[j];
            nbBoutonsAppuyes++;
        }
    }
    
    if (nbBoutonsAppuyes == 2 && questionAppuyee != -1 && reponseAppuyee != -1) {
        bool bonneReponse = false;
        for (int k = 0; k < maxReponses; k++) {
            if (correspondances[questionAppuyee][k] == reponseAppuyee) {
                bonneReponse = true;
                break;
            }
        }
        if (bonneReponse) {
            digitalWrite(ledVerte, HIGH);
            digitalWrite(ledRouge, LOW);
            Serial.println("VERT");
        } else {
            digitalWrite(ledVerte, LOW);
            digitalWrite(ledRouge, HIGH);
            Serial.println("ROUGE");
        }
        delay(300);
        digitalWrite(ledVerte, LOW);
        digitalWrite(ledRouge, LOW);
    } else {
        digitalWrite(ledVerte, LOW);
        digitalWrite(ledRouge, LOW);
    }
}
