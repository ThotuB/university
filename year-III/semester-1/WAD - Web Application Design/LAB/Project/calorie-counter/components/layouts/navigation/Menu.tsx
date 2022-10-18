import { useState } from "react";
import MenuItem from "./MenuItem";
import { DotsVerticalIcon, UserIcon, CogIcon, UserAddIcon, LogoutIcon, QuestionMarkCircleIcon } from '@heroicons/react/outline';
import { useUser } from "contexts/UserContext";
import Router from "next/router";

export default function DropdownMenu() {
    let [isOpen, setIsOpen] = useState(false);

    let { logOut } = useUser();

    const handleViewProfile = () => {

    }

    const handleSettings = () => {
        Router.push("/settings");
    }

    const handleAddFriend = () => {

    }

    const handleHelp = () => {

    }

    const handleLogout = async () => {
        try {
            await logOut();
            Router.push('/');
        }
        catch (error) {
            console.log(error);
        }
    }

    return (
        <div className="relative inline-block ">
            <button className="block text-gray-700 bg-white"
                onClick={() => setIsOpen(!isOpen)}
                onBlur={() => setTimeout(setIsOpen, 100, false)}
            >
                <DotsVerticalIcon className="w-5" />
            </button>

            <div className={`absolute right-0 w-48 py-2 border mt-2 bg-white rounded-md shadow-xl
                    ${isOpen ? "" : "hidden"}
                `}
            >
                <MenuItem icon={<UserIcon className="w-5" />} label="View Profile" onClick={handleViewProfile} />
                <MenuItem icon={<CogIcon className="w-5" />} label="Settings" onClick={handleSettings} />
                <hr className="border-gray-200" />
                <MenuItem icon={<UserAddIcon className="w-5" />} label="Invite Friends" onClick={handleAddFriend} />
                <hr className="border-gray-200" />
                <MenuItem icon={<QuestionMarkCircleIcon className="w-5" />} label="Help" onClick={handleHelp} />
                <MenuItem icon={<LogoutIcon className="w-5" />} label="Sign Out" onClick={handleLogout} />
            </div>
        </div>
    );
}