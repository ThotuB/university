import FoodGraph from './FoodGraph'
import { ChevronUpIcon, ChevronLeftIcon, PlusIcon } from '@heroicons/react/outline'
import Button from 'components/common/Button'
import Router from 'next/router'

interface FoodProps {
    id: number;
    name: string;
    description: string;
    calories: number;
    macros: {
        carbs: number;
        fat: number;
        protein: number;
        calories: number;
    };
    company: string;
    rating: number;
    servingSize: number;
    servingUnit: string;
}

export default function Food({ id, name, description, calories, macros, company, rating, servingSize, servingUnit }: FoodProps) {
    const handleSize = () => {

    }

    const handleAdd = () => {

    }

    const handleDetails = () => {
        Router.push(`/food/${id}`)
    }

    return (
        <div className="flex max-w-3xl w-full mx-auto overflow-hidden bg-white rounded-xl border">
            <div className="w-4/5 p-4 gap-2 flex flex-col justify-between">
                <div>
                    <div className="flex justify-between gap-2">
                        <div className="text-2xl font-bold text-purple-400">
                            {description}
                        </div>
                        {/* <div className="pt-1">
                            <Rating rating={rating} />
                        </div> */}
                    </div>

                    <div className="italic text-lg mt-1 font-semibold text-gray-700 px-2">
                        {company}
                    </div>
                </div>

                <div className="flex justify-between">
                    <div className="flex">
                        <div className="font-bold text-gray-700 text-2xl">
                            {calories} kcal
                        </div>
                        <div className="pl-2 self-center italic text-gray-500 font-light">
                            / {servingSize} {servingUnit}
                        </div>
                    </div>
                    <div className="flex gap-2">
                        <ChevronLeftIcon />
                        <Button onClick={handleSize} className="px-3">
                            <ChevronLeftIcon className="w-5" />
                            <ChevronUpIcon className="hidden " />
                        </Button>
                        <Button onClick={handleAdd} className="px-2">
                            <PlusIcon className='w-5' />
                        </Button>
                        <Button onClick={handleDetails}>
                            DETAILS
                        </Button>
                    </div>
                </div>
            </div>

            <FoodGraph macros={macros} calories={macros.calories} />
        </div>
    )
}