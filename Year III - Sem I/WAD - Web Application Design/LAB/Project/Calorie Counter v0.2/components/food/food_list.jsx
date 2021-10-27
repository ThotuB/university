import FoodItem from './food_item';

function FoodList(props) {
    const food_list = props.items.map((item) => {
        const { id, name, calories, company, author } = item;

        return (
            <FoodItem
                key={id}
                id={id}
                name={name}
                calories={calories}
                company={company}
                author={author}
            />
        );
    })

    return (
        <div>
            {food_list}
        </div>
    );
}

export default FoodList;