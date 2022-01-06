import UserRecipes from "./UserRecipes";
import RecipeItem from "./Recipe";
import { Recipe } from "./create/Form"

interface RecipesProps {
    recipes: Recipe[];
}

function Recipes({ recipes }: RecipesProps) {
    return (
        <div className="max-w-3xl m-auto flex flex-col items-center gap-6">
            <UserRecipes />
            {recipes.map(recipe => (
                <RecipeItem key={recipe.id}
                    name={recipe.name}
                    description={recipe.description}
                    date={recipe.date}
                />
            ))}
        </div>
    )
}

export default Recipes;