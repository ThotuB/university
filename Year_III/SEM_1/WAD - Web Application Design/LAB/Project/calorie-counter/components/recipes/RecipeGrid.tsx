import { RecipeSummaryDto } from "types/recipe";
import RecipeItem from "./Recipe";

interface RecipesProps {
    recipes: RecipeSummaryDto[],
    onDelete?: (id: string) => void;
    onApprove?: (id: string, approval: boolean) => void;
    editable?: boolean,
}

function Recipes({ recipes, onDelete, onApprove, editable }: RecipesProps) {
    return (
        <div className="w-full grid grid-cols-2 gap-6">
            {recipes.map(recipe => (
                <RecipeItem
                    key={recipe.id}
                    recipe={recipe}
                    onDelete={onDelete}
                    onApprove={onApprove}
                    editable={editable}
                />
            ))}
        </div>
    )
}

export default Recipes;