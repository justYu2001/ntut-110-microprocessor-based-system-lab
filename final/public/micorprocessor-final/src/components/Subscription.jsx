import React from "react";
import { ReactComponent as BellIcon } from '../assets/icons/bell.svg';

const SubscriptionButton = (props) => {
    const { onClick } = props;

    return (
        <button className="bg-white w-12 h-12 flex justify-center items-center rounded-full absolute bottom-4 right-4 text-stone-300 hover:text-sky-400"
         onClick={onClick}
        >
            <BellIcon className="w-6 h-6"></BellIcon>
        </button>
    );
};

export default SubscriptionButton;