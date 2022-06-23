import React from "react";

import Video from "./components/Video";
import Dashboard from "./components/Dashboard";

const App = () => {
    return (
        <div className="w-screen h-screen bg-gradient-to-r from-cyan-400 to-sky-500 flex justify-center items-center">
            <div className="w-1/2 max-w-[1280px]">
                <Video></Video>
                <Dashboard></Dashboard>
            </div>
        </div>
    )
}

export default App;