import axios, { AxiosResponse } from "axios";
import { FoodsDto } from "types/food";

const apiKey = "U90ctjxNwICMOKnJnyqB2kDuKgpqL2dG7vBB03lZ"

export const searchFoods = (name: string, page: number, pageSize: number = 10, dataType: string = "Branded"): Promise<AxiosResponse<FoodsDto>> => {
    const url = `https://api.nal.usda.gov/fdc/v1/search`
    const query = {
        params: {
            api_key: apiKey,
            generalSearchInput: name,
            dataType: dataType,
            pageNumber: page,
            pageSize: pageSize,
        }
    }

    return axios.get(url, query)
}