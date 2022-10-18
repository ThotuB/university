import { useUser } from "contexts/UserContext";
import Profile from "./Profile";
import UserProfile from "./UserProfile";

interface ProfilePageProps {
    uid: string;
}

export default function ProfilePage({ uid }: ProfilePageProps) {
    const { user } = useUser();

    return (
        <div className="max-w-5xl w-full flex flex-col gap-4">
            {user?.uid === uid ? 
                <UserProfile uid={uid} /> :
                <Profile uid={uid} />
            }
        </div>
    )
}
