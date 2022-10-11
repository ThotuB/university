import Button from "components/common/Button";
import TextField from "components/common/TextField";
import { useUser } from "contexts/UserContext";
import { useState } from "react";
import EditProfileField from "../form/SettingsField";

export default function AdminApplication() {
    const [token, setToken] = useState("");

    const {user, admin, makeUserAdmin} = useUser();

    const handleAdminApplication = async () => {
        if (!user) return
        try {
            await makeUserAdmin(user, token);
        }
        catch (err) {
            console.log(err)
        }
    }

    return (
        <div className="w-full grid grid-cols-5 grid-flow-row gap-x-10 gap-y-3 items-center">
            <EditProfileField label="Admin Token">
                <TextField value={token} onChange={(e) => setToken(e.target.value)} disabled={admin}/>
            </EditProfileField>
            <EditProfileField>
                {admin ? 
                    <Button className="bg-emerald-300 hover:bg-emerald-300 cursor-default">
                        Already Admin
                    </Button> :
                    <Button onClick={handleAdminApplication}>
                        Apply
                    </Button>
                }
            </EditProfileField>
        </div>
    )
}
