function RecipeCategory(props) {
    const { category } = props;

    return (
        <button className="text-xs font-medium text-purple-600 uppercase hover:font-semibold hover:italic">
            #{category}
        </button>
    )
}

export default RecipeCategory;