# Door Monitor

This project monitors the status of two doors and sends text messages when either door is opened. You can adjust the time that the system is armed and disarmed to avoid nuisance messages when high activity is expected. The main code runs on a Particle Photon and leverages the Particle Cloud to trigger Plivo to send the text messages.

## Hardware

The Particle Photon has two inputs. Each has a pullup resistor and is connected to a normally closed magnetic door switch which is connected to ground. In this case, there is a door monitored by the D1 input and a garage gate monitored by the D2 input.

## Instructions

Use the following template in a Particle Webhook to get Plivo to send a text message:

```
{
    "event": "back-door-status",
    "url": "https://api.plivo.com/v1/Account/PLIVOACCOUNTNUMBERGOESHERE/Message/",
    "requestType": "POST",
    "noDefaults": true,
    "rejectUnauthorized": false,
    "headers": {
        "Content-Type": "application/json"
    },
    "json": {
        "published_at": "{{{PARTICLE_PUBLISHED_AT}}}",
        "src": "15551234567",
        "dst": "15557654321",
        "text": "Back door has been opened",
        "event": "{{{PARTICLE_EVENT_NAME}}}",
        "data": "{{{PARTICLE_EVENT_VALUE}}}",
        "coreid": "{{{PARTICLE_DEVICE_ID}}}"
    },
    "auth": {
        "username": "PLIVOUSERNAMEGOESHERE",
        "password": "PLIVOCREDENTIALGOESHERE"
    }
}
```

## Built With

* [Particle](https://www.particle.io/) - Hardware and cloud IoT platform
* [Plivo](https://www.plivo.com/) - SMS API and Voice API platform
