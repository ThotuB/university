import ToggleSwitch from "components/common/ToggleSwitch";

export default function Preferences() {
    return (
        <div className="flex gap-4">
            <div className="text-xl">
                Theme
            </div>
            <ToggleSwitch />
        </div>
    )
}
