import { Fragment, useState } from "react"

interface SettingGroupProps {
    children: React.ReactElement<SettingPageProps>[];
}

interface SettingPageProps {
    children: React.ReactNode;
    title: string;
}

export function SettingPage({ children, title }: SettingPageProps) {
    return (
        <div className="px-32 py-8 w-4/5 h-full">
            {children}
        </div>
    )
}

export function SettingGroup({ children }: SettingGroupProps) {
    const [selected, setSelected] = useState(0)

    const handleSelect = (index: number) => {
        setSelected(index)
    }

    return (
        <div className="w-full border bg-white flex rounded overflow-hidden">
            <div className="w-1/5 border-r flex flex-col text-lg">
                {children.map(({props: {children, title}}, index) => {
                    return (
                        <Fragment key={index}>
                            {index === selected ? 
                                <div className="border-l-2 border-purple-400 font-bold text-purple-400 px-8 py-4">
                                    {title}
                                </div> :
                                <div className="border-l-2 border-white px-8 py-4 cursor-pointer hover:border-gray-200 hover:bg-gray-100"
                                    onClick={() => handleSelect(index)}
                                >
                                    {title}
                                </div>
                            }
                        </Fragment>
                    )
                })}
            </div>
            {children[selected]}
        </div>
    )
}
