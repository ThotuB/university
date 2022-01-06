import AccountIcon from 'components/common/AccountIcon'
import RecipeTag from './RecipeTag'

interface RecipeProps {
    name: string;
    description: string;
    date: string;
    img?: string;
    tags?: string[];
    account?: {
        accName: string;
        profilePic: string;
    }
}

function Recipe({ name, description, date, img, tags, account }: RecipeProps) {
    const { accName, profilePic } = account || { profilePic: '', accName: 'John' };

    return (
        <div className="max-w-3xl w-full overflow-hidden bg-white rounded-3xl shadow-md border">
            {img && <img className="w-full" src={img} alt="recipe" />}

            <div className="p-6 flex flex-col gap-2">
                <div className="flex gap-3">
                    {tags && tags.map(tag => <RecipeTag key={tag} tag={tag} />)}
                </div>
                <div className="text-2xl font-semibold text-gray-800 max-h-12">
                    {name}
                </div>
                <div className="text-sm text-gray-600 first-letter:ml-4">
                    {description}
                </div>

                <div className="mt-2 flex items-center gap-4">
                    <AccountIcon image={profilePic} name={accName} />
                    <div className="text-xs text-gray-600">
                        {date}
                    </div>
                </div>
            </div>
        </div>
    )
}

export default Recipe;