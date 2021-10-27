import Link from 'next/link';

function CreateRecipe(props) {
    return (
        <Link href="/recipes/create">
            <button className="border-8 rounded-3xl border-dashed border-purple-300 p-6 text-3xl w-full font-bold 
                hover:border-solid hover:bg-gray-100 hover:border-purple-400 transition-all duration-500 hover:scale-110"
            >
                + Add Recipe
            </button>
        </Link>
    )
}

export default CreateRecipe;