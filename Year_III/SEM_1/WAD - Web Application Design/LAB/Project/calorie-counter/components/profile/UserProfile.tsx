import Summary from "components/common/goal/Summary";
import { useUser } from "contexts/UserContext";
import Router from "next/router";
import ProfileInfo from "./ProfileInfoContainer";
import ProfileRecipes from "./ProfileRecipes";

interface UserProfileProps {
    uid: string;
}

export default function UserProfile({ uid }: UserProfileProps) {
    const handleAddRecipe = () => {
        Router.push('/recipes/create')
    }

    return (
        <div className="flex flex-col gap-4">
            <ProfileInfo uid={uid} />
            <Summary goal={2100} food={0} excercise={0} macros={{
                protein: 10,
                carbs: 30,
                fat: 50
            }} />
            <ProfileRecipes userId={uid} isUser />
            <button className="border-8 rounded-3xl border-dashed border-purple-300 p-6 text-3xl w-full font-bold 
                    hover:border-solid hover:bg-gray-100 hover:border-purple-400 transition-all duration-500 hover:scale-110"
                onClick={handleAddRecipe}
            >
                + Add Recipe
            </button>
        </div>
    )
}
