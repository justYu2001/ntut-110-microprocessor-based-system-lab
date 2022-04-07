// async function getLEDStatus(){
//     const a = await axios.get("/operations");
//     console.log(a);
//   }
//   getLEDStatus();




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
    for(let i = 0; i < 4 ; i++){
        temp['ledID'] = i + 1;
        if(ledStatusArray[i] === true){
            temp['operation'] = 'on';
        }
        else{
            temp['operation'] = 'off';
        }
        ledAll.push(temp);
        temp = {}
    }
    return ledAll;
}

let ledStatusArray = new Array(4).fill(false);

function print(data){
    let ledStatus = [];
    let temp = [];
    temp.push(`<ul>`)
    for(let i = 0; i < 4; i++){
        if(data[i] === true){
            ledStatus.push("On");
        }
        else{
            ledStatus.push("Off");
        }
        
        temp.push(`<li> LED ${i+1} is ${ledStatus[i]} </li> \n`);
        console.log(temp[i]);
    }  
    temp.push(`</ul>`);
    let ledString = '';
    for(let i = 0; i < 6; i++){
        ledString += temp[i];
    }
    console.log(ledString);
    ledLabel.innerHTML = ledString;
}

async function postData(data){
    let response = [];
    data.forEach(element => {
        response = (axios.post(`/operations`, element));
    });
    const ledStatus = await response;
    console.log(ledStatus.data.ledStatusList);
    print(ledStatus.data.ledStatusList);
}


document.getElementById('onAndOffbtn').addEventListener("click", btnclick);
function btnclick(){
    let first = document.getElementById("LED1").checked;
    let second = document.getElementById("LED2").checked;
    let third = document.getElementById("LED3").checked;
    let fourth = document.getElementById("LED4").checked;
    let ledArray = {first, second, third, fourth};
    let isOn = document.getElementById('onRadio').checked;
    switchLED(ledArray, isOn, ledStatusArray);
    let Data = saveData(ledStatusArray);
    postData(Data);
}

