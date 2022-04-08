const express = require('express');
const expressQueue = require('express-queue');
const { spawn } = require('child_process');
const dotenv = require('dotenv');

dotenv.config();

const queueMiddleware = expressQueue({
    activeLimit: 4,
    queuedLimit: -1,
});

const app = express();
app.use(express.static('public'));
app.use('/operations', queueMiddleware);
app.use(express.json());

const ledStatusList = [false, false, false, false];

function getOperationArguments(body) {
    const { ledID, operation, times } = body;

    if(ledID !== undefined && (ledID < 1 || ledID > 4)) {
        throw new Error('此 LED ID 不存在');
    }

    if(operation !== 'on' && operation !== 'off' && operation !== 'shine') {
        throw new Error('無法執行此操作');
    }

    if(operation === 'shine' && times === undefined) {
        throw new Error('沒有給定閃爍次數');
    }

    if((operation === 'on' || operation === 'off') && ledID === undefined) {
        throw new Error('沒有給定 LED ID');
    }

    if(operation == 'shine') {
        return ['-S', './gpio/gpio', operation, times];
    } else {
        return ['-S', './gpio/gpio', `LED${ledID}`, operation];
    }
}

async function controlGPIO(arguments) {
    const password = spawn("echo", [process.env.SUDO_PASSWORD]);
        
    const gpio = spawn('sudo', arguments, {
        stdio: [password.stdout, 'pipe', process.stderr]
    });

    if(gpio.stderr) {
        let error = '';
        for await(const chunk of gpio.stderr) {
            error += chunk;
        }

        throw new Error(error);
    }
}


app.post('/operations', async (request, response) => {
    const { body } = request;
    const { ledID, operation } = body;

    try {
        const arguments = getOperationArguments(body);
        if(process.env.NODE_ENV === 'production') {
            await controlGPIO(arguments);
        }
    } catch (error) {
        response.status(400).send({ 
            error: error.message, 
        });
        console.error(error);
        return;
    }

    let time = 0;

    if(ledID) {
        ledStatusList[ledID - 1] = operation == 'on';
    }
    
    if(operation == 'shine') {
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