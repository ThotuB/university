import AccountIcon from 'components/common/AccountIcon'
import Button from 'components/common/Button';
import Router from 'next/router';
import RecipeTag from './RecipeTag'
import { TrashIcon, PencilAltIcon } from '@heroicons/react/outline'
import axios from 'axios';

interface RecipeProps {
    id: string;
    name: string;
    description: string;
    date: string;
    img: string;
    tags?: string[];
    account: {
        name: string;
        image?: string;
    }
    onDelete?: (id: string) => void;
    editable?: boolean;
}

function Recipe({ id, name, description, date, img, tags, account: { name: username, image: userimg }, onDelete, editable }: RecipeProps) {
    const handleViewRecipe = () => {
        Router.push(`/recipes/${id}`)
    }

    const handleEditRecipe = () => {
        Router.push(`/recipes/edit/${id}`)
    }

    return (
        <div className="w-full overflow-hidden bg-white rounded-3xl shadow-md border">
            {img && <img className="w-full" src={img} />}

            <div className="p-6 flex flex-col gap-2">
                {tags && <div className="flex gap-3">
                    {tags.map(tag => <RecipeTag key={tag} tag={tag} />)}
                </div>}
                <div className="text-2xl font-semibold text-gray-800 max-h-12">
                    {name}
                </div>
                <div className="text-sm text-gray-600 first-letter:ml-4">
                    {description}
                </div>

                <div className="flex justify-between">
                    <div className="flex items-center gap-4">
                        <AccountIcon image={userimg} name={username} />
                        <div className="text-xs text-gray-600">
                            {date}
                        </div>
                    </div>
                    <div className="flex items-center gap-2">
                        {editable &&
                            <Button className="bg-emerald-400" onClick={handleEditRecipe}>
                                <PencilAltIcon className="w-6"/>
                            </Button>}
                        {onDelete &&
                            <Button className="bg-red-400" onClick={() => onDelete(id)}>
                                <TrashIcon className="w-6"/>
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