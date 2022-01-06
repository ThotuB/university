interface RecipeTagProps {
    tag: string;
}

function RecipeTag({ tag }: RecipeTagProps) {
    return (
        <button className="text-xs font-medium text-purple-600 uppercase hover:font-semibold hover:italic">
            #{tag}
        </button>
    )
}

export default RecipeTag;