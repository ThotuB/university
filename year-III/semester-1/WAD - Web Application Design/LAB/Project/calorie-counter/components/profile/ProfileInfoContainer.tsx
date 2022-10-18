import { useEffect, useState } from "react";
import { getUserProfile } from "services/user";
import { ProfileDto } from "types/profile";
import ProfileInfo from "./ProfileInfo";

interface ProfileInfoProps {
    uid: string;
}

export default function ProfileInfoContainer({ uid }: ProfileInfoProps) {
    const [loading, setLoading] = useState(true);
    const [profileInfo, setProfileInfo] = useState<ProfileDto>({} as ProfileDto);

    useEffect(() => {
        getUserProfile(uid)
            .then(res => {
                setProfileInfo(res.data);
                setLoading(false);
            })
    }, [uid])

    return (
        <div className="w-full bg-white rounded-xl border">
            {loading || 
                <ProfileInfo info={profileInfo}/>
            }
        </div>
    )
}
