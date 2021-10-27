import { useState } from "react";
import MenuItem from "./MenuItem";
import { DotsVertical, User, Cog, UserAdd, Logout, Help } from "../svg/Heroicons"

function DropdownMenu() {
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
        <MenuItem svg={<User/>} name={"View Profile"} href={'#'}/>
        <MenuItem svg={<Cog/>} name={"Settings"} href={'#'}/>
        <hr className="border-gray-200" />
        <MenuItem svg={<UserAdd/>} name={"Invite Friends"} href={'#'}/>
        <hr className="border-gray-200" />
        <MenuItem svg={<Help/>} name={"Help"} href={'#'}/>
        <MenuItem svg={<Logout/>} name={"Sign Out"} href={'/'}/>
      </div>
    </div>
  );
}

export default DropdownMenu;