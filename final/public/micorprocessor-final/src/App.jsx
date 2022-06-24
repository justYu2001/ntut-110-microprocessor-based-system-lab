import React, { useState } from "react";

import Video from "./components/Video";
import Dashboard from "./components/Dashboard";
import SubscriptionButton from "./components/Subscription";
import LineBotModal from "./components/LineBotModal";


const App = () => {
    const [isLineBotModalOpen, setIsLineBotModalOpen] = useState(false);

    const openLineBotModal = () => setIsLineBotModalOpen(true);
    const closeLineBotModal = () => setIsLineBotModalOpen(false);

    return (
        <>
            <LineBotModal isOpen={isLineBotModalOpen} onClose={closeLineBotModal}></LineBotModal>
            <div className="w-screen h-screen bg-gradient-to-r from-cyan-400 to-sky-500 flex justify-center items-center relative">
                <div className="w-1/2 max-w-[1280px]">
                    <Video></Video>
                    <Dashboard></Dashboard>
                </div>
                <SubscriptionButton onClick={openLineBotModal}></SubscriptionButton>
            </div>
        </>
    )
}

export default App;