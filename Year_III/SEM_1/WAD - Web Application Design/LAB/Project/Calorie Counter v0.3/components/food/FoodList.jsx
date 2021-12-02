import FoodItem from './FoodItem';

function FoodList(props) {
    const food_list = props.items.map((item) => {
        const { id, name, macros, calories, company, author, img, rating } = item;

        return (
            <FoodItem
                key={id}
                id={id}
                name={name}
                macros={macros}
                calories={calories}
                company={company}
                author={author}
                img={img}
                rating={rating}
            />
        );
    })

    return (
        <div className='flex flex-col gap-4 mb-4'>
            {food_list}
        </div>
    );
}

export default FoodList;