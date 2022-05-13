function switchLED(ledArray,isOn,ledStatusArray){
    let count = 0;
    for(let i in ledArray){
        if(ledArray[i] == true){
            ledStatusArray[count] = isOn;
        }
        count += 1;
    }
}
function saveData(ledStatusArray){
    temp ={}
    let ledAll = [];
    for(let i = 0; i < 2 ; i++){
        ledAll.push(ledStatusArray[i]);
        temp = {}
    }
    return ledAll;
}

let ledStatusArray = new Array(2).fill(false);

function print(data){
    let ledStatus = [];
    let temp = [];
    temp.push(`<ul>`)
    for(let i = 0; i < 2; i++){
        if(data[i] === true){
            ledStatus.push("On");
        }
        else{
            ledStatus.push("Off");
        }
        
        temp.push(`<li> LED ${i+1} is ${ledStatus[i]} </li> \n`);
    }  
    temp.push(`</ul>`);
    let ledString = '';
    for(let i = 0; i < 4; i++){
        ledString += temp[i];
    }
    
    ledLabel.innerHTML = ledString;
}

let shiningTime;

function shining(){
    if(shiningTime % 2 == 0){
        print([true,false]);
    }
    else{
        print([false,true]);
    }
    shiningTime -= 1;
    if(shiningTime < 0){
        clearInterval(intervalID);
        print([false,false]);
        btn.disabled = false;
    }
}

async function postOnAndOffData(data){
    let response = [];
    let dataPost = {};
    dataPost['operation'] = "set state";
    dataPost['stateList'] = data;
    response = await (axios.post(`/operations`, dataPost));
    const ledStatus = response;
    console.log(ledStatus.data.stateList);
    print(ledStatus.data.stateList);
}

async function postShiningData(times){
    data = {};
    data['operation'] = "shine";
    data['times'] = times;
    const ledStatus = await axios.post(`/operations`,data);
    let time = ledStatus.data.time;
    intervalID = setInterval(shining,time);
}

const OnBtn = document.getElementById('onAndOffbtn');
document.getElementById('onAndOffbtn').addEventListener("click", btnclick);
function btnclick(){
    let first = document.getElementById("LED1").checked;
    let second = document.getElementById("LED2").checked;
    let ledArray = {first, second};
    let isOn = document.getElementById('onRadio').checked;
    switchLED(ledArray, isOn, ledStatusArray);
    let Data = saveData(ledStatusArray);
    postOnAndOffData(Data);
}
let  adcInterval;

const ADbtn = document.getElementById("ADCbtn");
ADbtn.addEventListener("click", ADCbtnclick);
function ADCbtnclick(){
    let isOn = document.getElementById('Detect').checked;
    if(isOn === true){
        adcInterval = setInterval(function(){
            axios.get('/adc')
            .then(function (response) {
              console.log(response.data);
              adclabel.innerText = response.data;
            })
        },1000);
    }
    else{
        clearInterval(adcInterval);
    }
}

const btn = document.getElementById('shiningBtn');
btn.addEventListener("click", shiningbtnclick);
function shiningbtnclick(){
    let ledData = [];
    let times = document.getElementById("timesInput").value;
    shiningTime = times * 2;
    postShiningData(times);
    btn.disabled = true;
}