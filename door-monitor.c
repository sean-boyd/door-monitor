// This is the time the alarm is disabled every weekday morning
const int alarmOffHour = 8;
const int alarmOffMin = 30;

// This is the time the alarm is enabled every weekday evening
const int alarmOnHour = 18;
const int alarmOnMin = 00;

// This sets the alarm to always be armed. TRUE=on, FALSE=follow times set above
const bool alarmAlwaysOn = true;

const bool CLOSED = 0;
const bool OPEN = 1;

const int LED = D7;
const int doorSwitch = D1;
const int gateSwitch = D2;

bool doorStatus = CLOSED;
bool doorStatusLastState = CLOSED;

bool gateStatus = CLOSED;
bool gateStatusLastState = CLOSED;


void setup() {
    Particle.variable("doorStatus", doorStatus);
    Particle.variable("gateStatus", gateStatus);
    
    Time.zone(-7);  // Set time zone to PST
    //Time.beginDST();   // Comment out when DST is not in effect (2am on Mar 8 2020 and ends on Nov 1 2020)

    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW); //Turn LED off
    
    pinMode(doorSwitch, INPUT_PULLUP);
    pinMode(gateSwitch, INPUT_PULLUP);
    }


void loop() {
    
    checkDoorStatus();
    if(doorStatus != doorStatusLastState) {
        if(checkTime()) {
            if(doorStatus == OPEN) {
                Particle.publish("back-door-status", "Open");
                digitalWrite(LED, HIGH);
            } else {
                //Particle.publish("back-door-status", "Closed");
                digitalWrite(LED, LOW);
            } 
        }
        doorStatusLastState = doorStatus;
    }
    
    checkGateStatus();
    if(gateStatus != gateStatusLastState) {
        if(checkTime()) {
            if(gateStatus == OPEN) {
                Particle.publish("back-gate-status", "Open");
                digitalWrite(LED, HIGH);
            } else {
                //Particle.publish("back-gate-status", "Closed");
                digitalWrite(LED, LOW);
            } 
        }
        gateStatusLastState = gateStatus;
    }
    
    delay(1000);
    }


void checkDoorStatus() {
    doorStatus = digitalRead(doorSwitch);
}


void checkGateStatus() {
    gateStatus = digitalRead(gateSwitch);
}


bool checkTime() {
    
    // Always trigger, regardless of time and day. Comment out if you want to use the logic below.
    if (alarmAlwaysOn) return true;
    
    // Always trigger on the weekend.
    if (Time.weekday() == 1 || Time.weekday() == 7) return true;
    
    // On a weekday, check the following:
    
    // If it's well before work starting
    if (Time.hour() < alarmOffHour) return true;
    
    // If it's close to work starting
    if (Time.hour() == alarmOffHour) {
        if (Time.minute() < alarmOffMin) return true;
        else return false;
    }
    
    // If it's close to work ending
    if (Time.hour() == alarmOnHour) {
        if (Time.minute() >= alarmOnMin) return true;
        else return false;
    }
    
    // If it's well after work ending
    if (Time.hour() > alarmOnHour) return true;
    
    return false;
}