import Button from "components/common/Button"
import TextArea from "components/common/TextArea"
import TextField from "components/common/TextField"
import { useUser } from "contexts/UserContext"
import { useState } from "react"
import EditProfileField from "../form/SettingsField"

export default function ChangePassword() {
    const { user } = useUser()

    const [oldPassword, setOldPassword] = useState("")
    const [newPassword, setNewPassword] = useState("")
    const [confirmPassword, setConfirmPassword] = useState("")

    return (
        <div className="w-full flex flex-col justify-center items-center">
            <div className="flex gap-">

            </div>
            <div className="w-full grid grid-cols-5 grid-flow-row gap-x-10 gap-y-3 items-center">
                <EditProfileField label="Old password">
                    <TextField value={oldPassword} onChange={(e) => setOldPassword(e.target.value)}/>
                </EditProfileField>
                <EditProfileField label="New password">
                    <TextField value={newPassword} onChange={(e) => setNewPassword(e.target.value)}/>
                </EditProfileField>
                <EditProfileField label="Confirm new password">
                    <TextField value={confirmPassword} onChange={(e) => setConfirmPassword(e.target.value)}/>
                </EditProfileField>
                <EditProfileField>
                    <Button >
                        Change Password
                    </Button>
                </EditProfileField>
            </div>
        </div>
    )
}
