import RecipeItem from "./Recipe";

interface RecipesProps {
    recipes: {
        id: string;
        name: string;
        description: string;
        date: string;
        image: string;
        tags?: string[];
        user: {
            name: string;
            image?: string;
        }
    }[],
    onDelete?: (id: string) => void;
    editable?: boolean,
}

function Recipes({ recipes, onDelete, editable }: RecipesProps) {
    return (
        <div className="w-full m-auto flex flex-col items-center gap-6">
            {recipes.map(recipe => (
                <RecipeItem
                    key={recipe.id}
                    id={recipe.id}
                    name={recipe.name}
                    description={recipe.description}
                    img={recipe.image}
                    date={recipe.date}
                    account={recipe.user}
                    onDelete={onDelete}
                    editable={editable}
                />
            ))}
        </div>
    )
}

export default Recipes;