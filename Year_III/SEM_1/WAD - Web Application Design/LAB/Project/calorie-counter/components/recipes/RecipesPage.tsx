import { useUser } from "contexts/UserContext"
import FilteredRecipes from "./FilteredRecipes"
import UserRecipes from "./UserRecipes"

export default function RecipesPage() {
    const { user } = useUser()

    return (
        <div className="flex flex-col gap-6 max-w-3xl">
            {user && <UserRecipes userId={user.uid} />}
            <FilteredRecipes />
        </div>
    )
}