import AccountIcon from 'components/common/AccountIcon'
import Button from 'components/common/Button';
import Router from 'next/router';
import RecipeTag from './RecipeTag'
import { TrashIcon, PencilAltIcon, BadgeCheckIcon } from '@heroicons/react/solid'
import { RecipeSummaryDto } from 'types/recipe';

interface RecipeProps {
    recipe: RecipeSummaryDto
    onDelete?: (id: string) => void;
    onApprove?: (id: string, approval: boolean) => void;
    editable?: boolean;
}

function Recipe({recipe: { id, name, description, date, image, tags, approved=false, user: { name: username, image: userimg, id: uid }}, onDelete, onApprove, editable }: RecipeProps) {
    const handleViewRecipe = () => {
        Router.push(`/recipes/${id}`)
    }

    const handleEditRecipe = () => {
        Router.push(`/recipes/edit/${id}`)
    }

    return (
        <div className="w-full overflow-hidden bg-white rounded-3xl border flex flex-col">
            {image && <img className="w-full" src={image} />}
            <div className="p-6 flex flex-col justify-between gap-3 grow">
                <div className="flex flex-col gap-3">
                    {tags && <div className="flex gap-3">
                        {tags.map(tag => <RecipeTag key={tag} tag={tag} />)}
                    </div>}
                    <div className="flex items-center gap-2 text-2xl font-semibold text-gray-800 max-h-12 uppercase">
                        {name}
                        {approved &&
                            <div className='text-purple-400 flex gap-1 items-center'>
                                <BadgeCheckIcon className="w-7" />
                            </div>}
                    </div>
                    <div className="text-sm text-gray-600 first-letter:ml-4">
                        {description}
                    </div>
                </div>
                <div className="flex justify-between">
                    <div className="flex items-center gap-4">
                        <AccountIcon image={userimg} name={username} id={uid} />
                        <div className="text-xs text-gray-600">
                            {date}
                        </div>
                    </div>
                    <div className="flex items-center gap-2">
                        {onApprove &&
                            <Button className="bg-purple-300" onClick={() => onApprove(id, !approved)}>
                                <BadgeCheckIcon className="w-6" />
                            </Button>}
                        {editable &&
                            <Button className="bg-emerald-400" onClick={handleEditRecipe}>
                                <PencilAltIcon className="w-6" />
                            </Button>}
                        {onDelete &&
                            <Button className="bg-red-400" onClick={() => onDelete(id)}>
                                <TrashIcon className="w-6" />
                            </Button>}
                        <Button onClick={handleViewRecipe}>
                            View Recipe
                        </Button>
                    </div>
                </div>
            </div>
        </div>
    )
}

export default Recipe;