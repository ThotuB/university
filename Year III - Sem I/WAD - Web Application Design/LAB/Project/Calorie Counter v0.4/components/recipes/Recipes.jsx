import CreateRecipe from "./CreateRecipe";
import RecipeItem from "./RecipeItem";

function Recipes() {
    return (
        <div className="max-w-3xl m-auto flex flex-col items-center gap-6">
            <CreateRecipe />
            <RecipeItem
                categories={["Breakfast", "Lunch", "Dinner"]}
                name="Name"
                description="This is a description"
                date="21 SEP 2015"
            />
        </div>
    )
}

export default Recipes;