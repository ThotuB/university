import Rating from './Rating';
import FoodGraph from './FoodGraph';
import { ChevronUp, ChevronLeft, Plus } from '../svg/Heroicons'
import Button from '../common/Button'

function FoodItem(props) {
    const { id, name, calories, macros, company, author, img, rating } = props;

    return (
    <div className="flex max-w-3xl w-full mx-auto overflow-hidden bg-white rounded-xl drop-shadow-md border">
        <div className="w-1/5">
            <img className="object-cover"/>
        </div>

        <div className="w-3/5 p-4 flex flex-col justify-between">
            <div>
                <div className="flex justify-between items-center">
                    <div className="text-2xl font-bold text-purple-400">
                        {name}
                    </div>
                    <Rating rating={rating} />
                </div>

                <div className="italic text-lg mt-1 font-semibold text-gray-700 px-2">
                    {company}
                </div>
            </div>

            <div className="flex justify-between">
                <div className="flex">
                    <div className="font-bold text-gray-700 text-2xl">
                        {calories}
                    </div>
                    <div className="pl-2 self-center italic text-gray-500 font-light">
                        / 100g
                    </div>
                </div>
                <div className="flex gap-2">
                    <button className="text-sm font-bold text-white transition-colors duration-200 transform bg-gray-800 rounded-md hover:bg-purple-400">
                        <ChevronLeft className="mx-2 my-2"/>
                        <ChevronUp className="hidden mx-2 my-2"/>
                    </button>
                    <button className="px-2 py-2 text-sm font-bold text-white transition-colors duration-200 transform bg-gray-800 rounded-md hover:bg-purple-400">
                        <Plus />
                    </button>
                    <Button>
                        DETAILS
                    </Button>
                </div>
            </div>
        </div>

        <FoodGraph macros={macros} calories={calories}/>
    </div>
    );
}

export default FoodItem;