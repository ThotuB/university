import { useState } from "react";
import MenuItem from "./MenuItem";
import { DotsVertical, User, Cog, UserAdd, Logout, Help } from "components/common/svg/Heroicons";

export default function DropdownMenu() {
    let [isOpen, setIsOpen] = useState(false);

    return (
        <div className="relative inline-block ">
            <button className="block text-gray-700 bg-white"
                onClick={() => setIsOpen(!isOpen)}
                onBlur={() => setTimeout(setIsOpen, 100, false)}
            >
                <DotsVertical />
            </button>

            <div className={`absolute right-0 w-48 py-2 border mt-2 bg-white rounded-md shadow-xl
                    ${isOpen ? "" : "hidden"}
                `}
            >
                <MenuItem icon={<User/>} label="View Profile" href={'#'}/>
                <MenuItem icon={<Cog/>} label="Settings" href={'/settings'}/>
                <hr className="border-gray-200" />
                <MenuItem icon={<UserAdd/>} label="Invite Friends" href={'#'}/>
                <hr className="border-gray-200" />
                <MenuItem icon={<Help/>} label="Help" href={'#'}/>
                <MenuItem icon={<Logout/>} label="Sign Out" href={'/'}/>
            </div>
        </div>
    );
}