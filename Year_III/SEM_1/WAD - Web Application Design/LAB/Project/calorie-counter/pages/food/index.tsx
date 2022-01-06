import FoodList from 'components/food/Foods';
import Summary from 'components/common/goal/Summary';
import Loading from 'components/common/Loading';
import Pagination from 'components/common/pagination/Pagination';
import Layout from 'components/layouts/navigation/Layout';
import { useState, useEffect } from 'react';
import { GetServerSideProps } from 'next';
import axios from 'axios';

interface Props {
    apiKey: string;
    page: number;
    search: string;
}

export default function Index({ apiKey, page, search }: Props) {
    const [foods, setFoods] = useState([]);
    const [pages, setPages] = useState(0);
    const [total, setTotal] = useState(0);
    const [loading, setLoading] = useState(true);

    useEffect(() => {
        const url = `https://api.nal.usda.gov/fdc/v1/search`
        const query = {
            params: {
                api_key: apiKey,
                generalSearchInput: search,
                dataType: 'Branded',
                pageNumber: page,
                pageSize: 10,
            }
        }

        axios.get(url, query)
            .then(res => {
                setFoods(res.data.foods);
                setPages(res.data.totalPages);
                setTotal(res.data.totalHits);
                setLoading(false);
            })
            .catch(err => {
                console.log(err);
            })
    }, [search, page]);

    return (
        <Layout>
            <div className="flex flex-col gap-6">
                <Summary />
                {loading ? <Loading /> : <FoodList items={foods} />}
                <Pagination page={page} pages={pages} entriesPerPage={10} entriesTotal={total} />
            </div>
        </Layout>
    );
}

export const getServerSideProps: GetServerSideProps = async (context) => {
    const apiKey = process.env.USDA_API_KEY;
    const page = parseInt(context.query.page as string) || 1;
    const search = context.query.search || '';

    return {
        props: {
            apiKey: apiKey,
            page: page,
            search: search
        }
    }
}