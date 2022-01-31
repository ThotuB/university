import Button from "components/common/Button"
import TextArea from "components/common/TextArea"
import TextField from "components/common/TextField"
import { useUser } from "contexts/UserContext"
import { useState } from "react"
import EditProfileField from "../form/SettingsField"

export default function EditProfile() {
    const { user } = useUser()

    const [name, setName] = useState(user?.displayName || "")
    const [website, setWebsite] = useState("")
    const [bio, setBio] = useState("")
    const [email, setEmail] = useState(user?.email || "")
    const [phone, setPhone] = useState("")
    const [gender, setGender] = useState("")
    
    return (
        <div className="w-full flex flex-col justify-center items-center">
            <div className="flex gap-">

            </div>
            <div className="w-full grid grid-cols-5 grid-flow-row gap-x-10 gap-y-3 items-center">
                <EditProfileField label="Name">
                    <TextField value={name} onChange={(e) => setName(e.target.value)}/>
                </EditProfileField>
                <EditProfileField label="Website">
                    <TextField value={website} onChange={(e) => setWebsite(e.target.value)}/>
                </EditProfileField>
                <EditProfileField label="Bio">
                    <TextArea value={bio} onChange={(e) => setBio(e.target.value)}/>
                </EditProfileField>
                <EditProfileField label="Email addess">
                    <TextField value={email} onChange={(e) => setEmail(e.target.value)}/>
                </EditProfileField>
                <EditProfileField label="Phone number">
                    <TextField value={phone} onChange={(e) => setPhone(e.target.value)}/>
                </EditProfileField>
                <EditProfileField label="Gender">
                    <TextField value={gender} onChange={(e) => setGender(e.target.value)}/>
                </EditProfileField>
                <EditProfileField>
                    <Button >
                        Edit Profile
                    </Button>
                </EditProfileField>
            </div>
        </div>
    )
}
