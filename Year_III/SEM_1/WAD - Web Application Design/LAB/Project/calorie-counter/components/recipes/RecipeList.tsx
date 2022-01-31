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
        <div className="w-full m-auto flex flex-col items-center gap-6">
            {recipes.map((recipe, index) =>  (
                <RecipeItem
                    key={index}
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