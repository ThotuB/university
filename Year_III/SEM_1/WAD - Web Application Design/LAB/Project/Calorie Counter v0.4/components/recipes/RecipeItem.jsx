import AccountIcon from '../common/AccountIcon'

import Category from './RecipeCategory'

function RecipeItem(props) {
    const { img, categories, account, name, description, date } = props;
    const { accountImg, accountName } = account || { accountImg: '', accountName: 'John' };

    const image = img ? 
        <img className="object-cover w-full h-64" src={img} /> :
        <></>

    const categoriesList = categories.map((category, idx) => {
        return <Category key={idx} category={category} />
    });

    return (
        <div className="max-w-3xl w-full overflow-hidden bg-white rounded-3xl shadow-md border">
            {image}

            <div className="p-6 flex flex-col gap-2">
                <div className="flex gap-3">
                    {categoriesList}
                </div>
                <div className="text-2xl font-semibold text-gray-800 max-h-12">
                    {name}
                </div>
                <div className="text-sm text-gray-600 first-letter:ml-4">
                    {description}
                </div>

                <div className="mt-2 flex items-center gap-4">
                    <AccountIcon image={accountImg} name={accountName}/>
                    <div className="text-xs text-gray-600">
                        {date}
                    </div>
                </div>
            </div>
        </div>
    )
}

export default RecipeItem;