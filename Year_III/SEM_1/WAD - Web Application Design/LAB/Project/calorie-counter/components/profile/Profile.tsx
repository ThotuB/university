import ProfileInfoContainer from "./ProfileInfoContainer";
import ProfileRecipes from "./ProfileRecipes";

interface ProfileProps {
    uid: string;
}

export default function Profile({ uid }: ProfileProps) {
    return (
        <div className="flex flex-col gap-4">
            <ProfileInfoContainer uid={uid} />
            <ProfileRecipes userId={uid} />
        </div>
    )
}