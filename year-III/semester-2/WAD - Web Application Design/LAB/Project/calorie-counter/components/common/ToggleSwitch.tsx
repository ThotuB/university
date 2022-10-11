export default function ToggleSwitch() {
    return (
        <div className="rounded-full shadow w-20 h-10 relative">
            <input type="checkbox" className="opacity-0 w-full h-full cursor-pointer absolute" />
            <div className="w-8 h-8 bg-black m-1 rounded-full"/>
        </div>    
    )
}
