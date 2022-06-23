import React, { useState, useEffect } from "react";
import { ReactComponent as WarningIcon } from "../icons/warning.svg";
import { ReactComponent as SafeIcon } from '../icons/safe.svg';

const Dashboard = () => {
    const [websocket, setWebsocket] = useState(null);

    const [hasPerson, setHasPerson] = useState(true);

    useEffect(() => {
        const connectWebsocket = () => {
            let websocketURL = "";
    
            if (process.env.NODE_ENV === "development") {
                websocketURL = `ws://localhost:8000/websocket/has_person`;
            } else {
                websocketURL = `ws://${window.location.host}/websocket/has_person`;
            }
    
            setWebsocket(new WebSocket(websocketURL));
        }

        connectWebsocket();
    }, []);

    useEffect(() => {
        if (websocket) {
            websocket.onmessage = (event) => setHasPerson(event.data === "has person");
        }
    }, [websocket]);

    const [currentMode, setCurrentMode] = useState("自動模式");

    const handleModeButtonClick = (event) => {
        const mode = event.currentTarget.innerText;
        setCurrentMode(mode);
    }

    const ModeButton = (props) => {
        const { mode, isActive } = props;

        return (
            <button className={ `${isActive ? "text-sky-400" : "text-neutral-400" } font-bold pl-2 pr-3 py-1 rounded-full hover:bg-slate-200 hover:text-sky-400` }
             onClick={handleModeButtonClick}
            >
                {mode}
            </button>
        );
    };



    const cameraModeList = [ "白天模式", "夜晚模式", "自動模式" ];

    return (
        <div className="h-40 mt-6 py-3 bg-white rounded flex justify-center">
            <div className="w-4/5 flex items-center">
                <WarningIcon className="h-16 w-16 text-red-500"></WarningIcon>
                <div className="mx-6 flex-1">
                    <h3 className="mb-4 pb-5 px-2 border-b-4 font-bold text-4xl">監視器模式</h3>
                    <div className="tracking-wider">
                        {cameraModeList.map((mode) => {
                            return <ModeButton mode={mode} isActive={currentMode === mode}></ModeButton>
                        })}
                    </div>
                </div>
            </div>
            <div className="mx-3 pl-10 border-l-4 flex flex-col justify-center items-center">
                {hasPerson
                    ? <WarningIcon className="h-16 w-16 text-red-500"></WarningIcon>
                    : <SafeIcon className="h-16 w-16 text-green-400"></SafeIcon> 
                }
                <span className="mt-2 text-2xl text-center w-32">{hasPerson ? "有可疑人士" : "安全"}</span>
            </div>
        </div>
    );
}

export default Dashboard;