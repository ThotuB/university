interface IngredientsProps {
    ingredients: {
        name: string;
        quantity: number;
    }[]
}

export default function Ingredients({ ingredients }: IngredientsProps) {
    return (
        <div className="text-lg flex flex-col gap-2 px-5">
            {ingredients.map((ingredient, index) => (
                <div key={index} className="flex items-center gap-3">
                    <div className="rounded-full border-2 border-purple-400" />
                    <div>
                        {ingredient.quantity} {ingredient.name}
                    </div>
                </div>
            ))}
        </div>
    )
}