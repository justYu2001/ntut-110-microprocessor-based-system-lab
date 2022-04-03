const express = require('express');
const expressQueue = require('express-queue');
const { spawn } = require('child_process');
const dotenv = require('dotenv');

dotenv.config();

const queueMiddleware = expressQueue({
    activeLimit: 2,
    queuedLimit: -1,
});

const app = express();
app.use(express.static('public'));
app.use('/operations', queueMiddleware);
app.use(express.json());

const ledStatusList = [false, false, false, false];

function getOperationArguments(body) {
    const { ledID, operation } = body;

    if(ledID) {
        return ['-S', './gpio/gpio', `LED${ledID}`, operation];
    } else {
        return ['-S', './gpio/gpio', operation];
    }
}


app.post('/operations', async (request, response) => {
    const { body } = request;
    const { ledID, operation } = body;

    if(process.env.NODE_ENV == 'production') {
        const password = spawn("echo", [process.env.SUDO_PASSWORD]);
        const arguments = getOperationArguments(body);
        const gpio = spawn('sudo', arguments);
        password.stdout.pipe(gpio.stdin);

        let error = "";
        for await(const chunk of gpio.stderr) {
            error += chunk;
        }

        if(error.length > 0) {
            console.error(error);
            response.status(400).send(error);
        }
    } else {
        if(ledID < 1 || ledID > 4) {
            response.status(400).send('此 LED ID 不存在');
        } else if(operation !== 'on' && operation !== 'off' && operation !== 'shine') {
            response.status(400).send('無法執行此操作');
        }
    }
    
    let time = 0;
    if(ledID) {
        ledStatusList[ledID - 1] = operation == 'on';
    } else {
        time = 800;
        ledStatusList.forEach((elem, index) => {
            ledStatusList[index] = false;
        });
    }
    response.status(201).send({
        ledStatusList,
        time,
    });
});

const port = 3000;
app.listen(port, () => {
    console.log(`http://localhost:3000`);
});